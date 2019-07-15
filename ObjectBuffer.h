#ifndef objectbufferH
#define objectbufferH

#include "Object.h"

class MObjectBuffer
{
private:
	GLuint Id;
	GLenum Type;
	vector<stUVQuad> UVQuads;
	vector<MObject*> Objects;
	unsigned int ObjectsCount;
	unsigned int BindNumber;
	
	bool PreCheck(MObject* Object);
public:
	MObjectBuffer();
	~MObjectBuffer();
	
	bool Initialize(GLenum inType);
	bool AddObject(MObject* Object, float pX0, float pY0, float pW, float pH, float tX0, float tY0, float tW, float tH, unsigned int inTextureId);
	bool UpdateObject(MObject* Object);
	bool UpdateAll();
	void RemoveAll();
	bool DisposeAll();
	bool RemoveObject(MObject* Object, bool Force=true);
	void DrawObject(MObject* Object);
	void DrawAll();
	void SetBindNumber(unsigned char Number);
	void Bind(MObject* Object, unsigned char Number);
	void UnBind(unsigned char Number);
	void Begin();
	void End();
	
	void Close();
};

#endif
