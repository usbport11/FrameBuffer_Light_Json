#include "stdafx.h"
#include "Object.h"

MObject::MObject()
{
	BufferOffset = -1;
	NullUVQuad(UVQuad);
	TextureId = 0;
	DirectionRight = true;
}

MObject::~MObject()
{
	BufferOffset = -1;
	NullUVQuad(UVQuad);
	TextureId = 0;
	DirectionRight = true;
}

bool MObject::SetBufferOffset(int inBufferOffset)
{
	BufferOffset = inBufferOffset;
	return true;
}

bool MObject::SetTexture(unsigned int inTextureId)
{
	if(!inTextureId)
	{
		LogFile<<"Object: Wrong texture id"<<endl;
		return false;
	}
	TextureId = inTextureId;
	return true;
}

bool MObject::SetVertex(stQuad Vertex)
{
	if(BufferOffset < 0) return false;
	SetUVQuad(UVQuad, Vertex, GetUVQuad(UVQuad));
	return true;
}

bool MObject::SetUV(stQuad UV)
{
	if(BufferOffset < 0) return false;
	SetUVQuad(UVQuad, GetVertexQuad(UVQuad), UV);
	return true;
}

bool MObject::Set(stUVQuad inUVQuad)
{
	if(BufferOffset < 0) return false;
	UVQuad = inUVQuad;
	return true;
}
	
bool MObject::FlipTextureByX()
{
	if(BufferOffset < 0) return false;
	swap(UVQuad.p[0][1], UVQuad.p[3][1]);
	swap(UVQuad.p[1][1], UVQuad.p[2][1]);
	return true;
}

bool MObject::FlipTextureByY()
{
	if(BufferOffset < 0) return false;
	swap(UVQuad.p[0][1], UVQuad.p[1][1]);
	swap(UVQuad.p[2][1], UVQuad.p[3][1]);
	return true;
}

void MObject::SetDirectionRight(bool Right)
{
	DirectionRight = Right;
}

stQuad MObject::GetVertex()
{
	return GetVertexQuad(UVQuad);
}

stQuad MObject::GetUV()
{
	return GetUVQuad(UVQuad);
}

unsigned int MObject::GetTextureId()
{
	return TextureId;
}

int MObject::GetBufferOffset()
{
	return BufferOffset;
}

stUVQuad MObject::Get()
{
	return UVQuad;
}


