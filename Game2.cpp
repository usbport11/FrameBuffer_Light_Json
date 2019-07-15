#include "stdafx.h"
#include "Game2.h"

MGame2::MGame2():MWindow()
{
	Pause = true;
    Key = new bool [256];
    memset(Key, 0, 256);
	
	pDrawFunc = NULL;
	txUnit = NULL;

	CameraRound = 1000;
	CoordinateScale = 0.01; //1 metre - 100 pixels
	
	ViewScale = 1.0f;
	ViewOffset = -1.92f;
	ViewCenter = glm::vec2(0.0f, 0.0f);
	
	BlockSize[0] = 6;
	BlockSize[1] = 6;
	UnitSize = glm::vec2(0.32f, 0.32f);
	
	objLight = NULL;
	ambientColor = glm::vec4(0.3f, 0.3f, 0.7f, 0.7f);
	whiteColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	lightOffset = glm::vec2(0.1, 0.1);
}

MGame2::~MGame2()
{
	pDrawFunc = NULL;
}

bool MGame2::PrepareShaderValues()
{
	//prepare vertex array - for all programs
    glGenVertexArrays(1, &VertexArrayId);
	glBindVertexArray(VertexArrayId);
	GLenum Error = glGetError();
	if(Error != GL_NO_ERROR)
	{
		LogFile<<"Game2: "<<(char*)gluErrorString(Error)<<" "<<Error<<endl;
		return false;
	}
	
	LogFile<<"Game2: Load shaders"<<endl;
	ProgramId = LoadShaders((char*)"shaders/main2.vertexshader.glsl", (char*)"shaders/main2.fragmentshader.glsl");
	if(!ProgramId) return false;
	MVPId = glGetUniformLocation(ProgramId, "MVP");
	if(MVPId == -1)
	{
		LogFile<<"Game2: Can't get MVP uniform"<<endl;
		return false;
	}
	
	mainTextureId = glGetUniformLocation(ProgramId, "mainTexture");
	if(mainTextureId == -1)
	{
		LogFile<<"Game2: Can't get texture uniform"<<endl;
		return false;
	}
	lightTextureId = glGetUniformLocation(ProgramId, "lightMap");
	if(lightTextureId == -1)
	{
		LogFile<<"Game2: Can't get light map uniform"<<endl;
		return false;
	}
	
	UseOffsetVertexId = glGetUniformLocation(ProgramId, "useOffsetVertex");
	if(UseOffsetVertexId == -1)
	{
		LogFile<<"Game2: Can't get useoffset vertex uniform"<<endl;
		return false;
	}
	UseOffsetUVId = glGetUniformLocation(ProgramId, "useOffsetUV");
	if(UseOffsetUVId == -1)
	{
		LogFile<<"Game2: Can't get useoffset uv uniform"<<endl;
		return false;
	}
	AmbientColorId = glGetUniformLocation(ProgramId, "ambientColor");
	if(AmbientColorId == -1)
	{
		LogFile<<"Game2: Can't get ambient color uniform"<<endl;
		return false;
	}
	resolutionId = glGetUniformLocation(ProgramId, "resolution");
	if(resolutionId == -1)
	{
		LogFile<<"Game2: Can't get resolution uniform"<<endl;
		return false;
	}
	
	return true;
}

bool MGame2::Initialize(HINSTANCE hInstance)
{	
	if(!CreateMainWindow(hInstance)) return 0;

    LogFile<<"Game2: Initialize"<<endl;
    
    if(!WindowInitialized)
    {
    	LogFile<<"Game2: Window was not initialized"<<endl;
    	return 0;
	}
	
	//randomize
    LogFile<<"Game2: randomize rand by time"<<endl; 
    srand(time(NULL));
    
    //prepare view
	Projection = glm::ortho(0.0f, (float)WindowWidth * CoordinateScale, 0.0f, (float)WindowHeight * CoordinateScale, -5.0f, 5.0f);
	CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	CameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	Model = glm::mat4(1.0f);
	View = glm::lookAt(CameraPosition, CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
    MVPdefault = MVP = Projection * View * Model;
    
    //shaders
    if(!PrepareShaderValues()) return false;
	//frame buffer
	if(!FrameBuffer.Initialize(800, 600)) return false;
	
	//buffer with light objects
	if(!(txLight = TextureLoader.LoadTexture("textures/tex04.png", 1, 1, 0, txOne_cnt, GL_NEAREST, GL_CLAMP_TO_BORDER))) return false;
	objLight = new MObject;
	if(!LightBuffer.Initialize(GL_STATIC_DRAW)) return false;
	if(!LightBuffer.AddObject(objLight, 0, 0, 3, 3, 0, 0, 1, 1, txLight->Id)) return false;
	if(!LightBuffer.DisposeAll()) return false;
	LightBuffer.SetBindNumber(0);
	
	//buffer with level objects
	if(!(txUnit = TextureLoader.LoadTexture("textures/tex03.png", 5, 1, 0, txUnit_cnt, GL_NEAREST, GL_REPEAT))) return false;
	if(!CreateBlocksTemplates()) return false;
	if(!FillBufferByRandBlocks(4)) return false;
	LightBuffer.SetBindNumber(0);
	
	//last preparations
	Stop();
	pDrawFunc = &MGame2::DrawGame;
    
    return true;
}

void MGame2::Start()
{
    Pause = false;
}

void MGame2::Stop()
{
    Pause = true;
}

bool MGame2::CreateBlocksTemplates()
{
	int BlocksCount;
	int PlanesCount;
	vector<int> Data;
	stPlane AddPlane;
	stBlock AddBlock;
	char iStr[3];
	char jStr[3];
	
	if(!FileJSON.Read("blocks.json")) return false;
	if(!FileJSON.GetArray("size", &Data))
	{
		FileJSON.Close();
		return false;
	}
	if(!Data.size() || Data[0] < 6 || Data[1] < 6)
	{
		cout<<"Game2: Block template size is wrong"<<endl;
		FileJSON.Close();
		return false;
	}
	BlockSize[0] = Data[0];
	BlockSize[1] = Data[1];
	if(!FileJSON.GetValue("blocks", BlocksCount))
	{
		FileJSON.Close();
		return false;
	}
	if(txUnit_cnt < BlocksCount)
	{
		LogFile<<"Game2: Texures count less than blocks temlates count"<<endl;
		FileJSON.Close();
		return false;
	}
	cout<<"Size: "<<Data[0]<<" "<<Data[1]<<endl;
	cout<<"Blocks templates: "<<BlocksCount<<endl;
	
	//create blocks templates
	for(unsigned int i=0; i<BlocksCount; i++)
	{
		AddBlock.Planes.clear();
		memset(iStr, 0, 3);
		sprintf(iStr, "%d", i);
		if(!FileJSON.GetValue(iStr, "planes", PlanesCount))
		{
			FileJSON.Close();
			return false;
		}
		for(unsigned int j=0; j<PlanesCount; j++)
		{
			memset(jStr, 0, 3);
			sprintf(jStr, "%d", j);
			if(!FileJSON.GetArray(iStr, jStr, &Data))
			{
				FileJSON.Close();
				return false;
			}
			if(Data[0] + Data[2] > BlockSize[0] || Data[1] + Data[3] > BlockSize[1])
			{
				LogFile<<"Game2: Plane size more than block size"<<endl;
				FileJSON.Close();
				return false;
			}
			AddPlane.Pos[0] = Data[0]; AddPlane.Pos[1] = Data[1];
			AddPlane.Size[0] = Data[2]; AddPlane.Size[1] = Data[3];
			AddBlock.Planes.push_back(AddPlane);
		}
		Blocks.push_back(AddBlock);
	}
	
	FileJSON.Close();
	
	return true;
}

bool MGame2::FillBufferByRandBlocks(unsigned int CountBlocks)
{
	if(CountBlocks > Blocks.size() || !CountBlocks) return false;
	
	//clear objects
	LocalBuffer.RemoveAll();
	for(unsigned int i=0; i<objBlocks.size(); i++)
	{
		if(objBlocks[i]) delete objBlocks[i];
	}
	objBlocks.clear();
	
	//fill level by random blocks
	int RandBlock;
	if(!LocalBuffer.Initialize(GL_STATIC_DRAW)) return false;
	cout<<"Used templates: ";
	for(unsigned int i=0; i<CountBlocks; i++)
	{
		RandBlock = rand() % Blocks.size();
		cout<<RandBlock<<" ";
		for(unsigned int j=0; j<Blocks[RandBlock].Planes.size(); j++)
		{
			objBlocks.push_back(new MObject);
			if(!LocalBuffer.AddObject(objBlocks.back(),
				(BlockSize[0] * i + Blocks[RandBlock].Planes[j].Pos[0]) * UnitSize.x, Blocks[RandBlock].Planes[j].Pos[1] * UnitSize.y, Blocks[RandBlock].Planes[j].Size[0] * UnitSize.x, Blocks[RandBlock].Planes[j].Size[1] * UnitSize.y, 
				0, 0, Blocks[RandBlock].Planes[j].Size[0], Blocks[RandBlock].Planes[j].Size[1],
				txUnit[RandBlock].Id)) return false;
		}
	}
	if(!LocalBuffer.DisposeAll()) return false;
	cout<<endl;
	
	return true;
}

void MGame2::DrawGame()
{
	if(!Pause)
	{
	}
	
	//prepare shader, matrix, color, uniforms
	glUseProgram(ProgramId);
	glUniformMatrix4fv(MVPId, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(mainTextureId, 0);
	glUniform1i(lightTextureId, 1);
	glUniform2f(resolutionId, WindowWidth, WindowHeight);
	
	//all window + light circle into texture [FBOTextureId]
	FrameBuffer.Begin();
	glUniform4fv(AmbientColorId, 1, &whiteColor[0]);
	LightBuffer.Begin();
	LightBuffer.DrawAll();
	LightBuffer.End();
	FrameBuffer.End();
	
	glUniform4fv(AmbientColorId, 1, &ambientColor[0]);
	LocalBuffer.Begin();
	FrameBuffer.Bind(1);
	LocalBuffer.DrawAll();
	LocalBuffer.End();
}

void MGame2::OnDraw()
{
	if(pDrawFunc) ((*this).*(pDrawFunc))();
}

void MGame2::OnActivate(WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			if(pDrawFunc == &MGame2::DrawGame) Start();
			LogFile<<"Game2: window activated!"<<endl;
			break;
		case WA_INACTIVE:
			if(pDrawFunc == &MGame2::DrawGame) Stop();
			LogFile<<"Game2: window deactivated!"<<endl;
			break;
	}
}

void MGame2::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	Key[wParam] = 1;

	if(pDrawFunc == &MGame2::DrawGame)
	{
		if(Key[VK_ESCAPE])
		{
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);
			return;
		}
		if(Key['R'])
		{
			if(!FillBufferByRandBlocks(4))
			{
				MessageBox(NULL, "Sorry. Some error(s) ocurred. See log for details", "Error", 0);
				SendMessage(m_hWnd, WM_CLOSE, 0, 0);
			}
		}
		if(Key[VK_LEFT] || Key[VK_RIGHT])
		{
			stQuad Vertex = objLight->GetVertex();
			if(Key[VK_LEFT]) MoveQuad(Vertex, -lightOffset.x, 0);
			if(Key[VK_RIGHT]) MoveQuad(Vertex, lightOffset.x, 0);
			objLight->SetVertex(Vertex);
			LightBuffer.UpdateObject(objLight);
		}
		if(Key[VK_UP] || Key[VK_DOWN])
		{
			stQuad Vertex = objLight->GetVertex();
			if(Key[VK_UP]) MoveQuad(Vertex, 0, lightOffset.y);
			if(Key[VK_DOWN]) MoveQuad(Vertex, 0, -lightOffset.y);
			objLight->SetVertex(Vertex);
			LightBuffer.UpdateObject(objLight);
		}
	}
}

void MGame2::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	Key[wParam] = 0;
	if(pDrawFunc == &MGame2::DrawGame)
	{
	}
}

void MGame2::OnClose()
{
	Stop();
	LogFile<<"Game2: Stopped."<<endl;
	
	LightBuffer.Close();
	if(objLight) delete objLight;
	
	LocalBuffer.Close();
	for(unsigned int i=0; i<objBlocks.size(); i++)
	{
		if(objBlocks[i]) delete objBlocks[i];
	}
	
	LogFile<<"Game2: Local buffer free"<<endl;
	
	TextureLoader.DeleteTexture(txUnit, txUnit_cnt);
	TextureLoader.DeleteTexture(txLight, txOne_cnt);
	TextureLoader.Close();
	
	FrameBuffer.Close();
	
	glDeleteProgram(ProgramId);
	glDeleteVertexArrays(1, &VertexArrayId);
	LogFile<<"Game2: Shaders free"<<endl;
	
	if(Key) delete [] Key;
	LogFile<<"Game2: Keys free"<<endl;
}

void MGame2::OnSize()
{
	if(pDrawFunc == NULL) return;
	cout<<"Size function!"<<endl;
	
	SetViewScale(ViewScale);
	
	//change projection matix and default MVP
	Projection = glm::ortho(0.0f, (float)WindowWidth * CoordinateScale, 0.0f, (float)WindowHeight * CoordinateScale, -5.0f, 5.0f);
    MVPdefault = Model * Projection * glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//change viewport
	glViewport(0, 0, WindowWidth, WindowHeight);//IMPORTANT!
}

void MGame2::SetViewScale(float inViewScale)
{
	ViewScale = inViewScale;
	ViewCenter = glm::vec2((HalfWindowSize[0] + WindowWidth * (1.0f - ViewScale) * 0.5f) * CoordinateScale, (HalfWindowSize[1] + WindowHeight * (1.0f - ViewScale) * 0.5f) * CoordinateScale);
}
