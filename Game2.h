#ifndef game2H
#define game2H

#include "Window.h"
#include "TextureLoader.h"
#include "ObjectBuffer.h"
#include "FrameBuffer.h"
#include "FileJSON.h"

struct stPlane
{
	int Pos[2];
	int Size[2];
};

struct stBlock
{
	vector<stPlane> Planes;
};

class MGame2;

typedef void (MGame2::*VoidFunc) ();

class MGame2: public MWindow
{
private:
	VoidFunc pDrawFunc;
	
	//statuses
	bool Pause;
	bool* Key;
	
	//classes
	MTextureLoader TextureLoader;
	MObjectBuffer LocalBuffer;
	MObjectBuffer LightBuffer;
	MFileJSON FileJSON;
	
	//textures
	stTexture* txUnit;
	stTexture* txLight;
	unsigned int txUnit_cnt;
	unsigned int txOne_cnt;
	
	//shaders data
	GLuint VertexArrayId;
	GLuint ProgramId;
	GLuint MVPId;
	GLuint UseOffsetVertexId;
	GLuint UseOffsetUVId;
	GLuint AmbientColorId;
	GLuint mainTextureId;
	GLuint lightTextureId;
	GLuint resolutionId;
	bool PrepareShaderValues();
	
	//FBO - lights
	MObject* objLight;
	MFrameBuffer FrameBuffer;
	GLuint lightFBOId;
	GLuint FBOTextureId;
	glm::vec2 lightOffset;
	glm::vec4 ambientColor;
	glm::vec4 whiteColor;
	
	//matrixes and view
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;
	glm::mat4 MVPdefault;
	glm::vec3 CameraPosition;
	glm::vec3 CameraDirection;
	float CameraRound;
	float CoordinateScale; //diffrence between resolution and cordinate system (needed for box2d better reaction)
	float ViewScale;
	float ViewOffset;
	glm::vec2 ViewCenter;
	
	//level
	vector<MObject*> objBlocks;
	vector<stBlock> Blocks;
	unsigned int BlockSize[2];
	glm::vec2 UnitSize;
	bool CreateBlocksTemplates();
	bool FillBufferByRandBlocks(unsigned int CountBlocks);
	
	//draw functions
	void DrawGame();
	
	//local
	void Start();
	void Stop();
	
	//window overload functions
	void OnDraw();
	void OnActivate(WPARAM wParam);
	void OnKeyUp(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void OnSize();
	
	//scale test
	void SetViewScale(float inViewScale);
public:
	MGame2();
	~MGame2();
	bool Initialize(HINSTANCE hInstance);
	void OnClose();
};

#endif
