#include "stdafx.h"
#include "FrameBuffer.h"

MFrameBuffer::MFrameBuffer()
{
	Id = 0;
	TextureId = 0;
	ImageFormat = GL_RGBA;
	Format = GL_RGBA;
	Parameters[0] = GL_NEAREST;
	Parameters[1] = GL_NEAREST;
	Parameters[2] = GL_CLAMP_TO_EDGE;
	Parameters[3] = GL_CLAMP_TO_EDGE;
}

bool MFrameBuffer::SetParameters(GLint inImageFormat, GLenum inFormat, GLint MagF, GLint MinF, GLint WrapS, GLint WrapT)
{
	ImageFormat = inImageFormat;
	Format = inFormat;
	Parameters[0] = MagF;
	Parameters[1] = MinF;
	Parameters[2] = WrapS;
	Parameters[3] = WrapT;
	
	return true;
}

bool MFrameBuffer::Initialize(unsigned int inWidth, unsigned int inHeight)
{
	Width = inWidth;
	Height = inHeight;

	glGenFramebuffers(1, &Id);
	glBindFramebuffer(GL_FRAMEBUFFER, Id);
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, ImageFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Parameters[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Parameters[1]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Parameters[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Parameters[3]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureId, 0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LogFile<<"Game2: Framebuffer failed"<<endl;
		return false;
	}
	return true;
}

void MFrameBuffer::Bind(unsigned int Number)
{
	glActiveTexture(GL_TEXTURE0 + Number);
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void MFrameBuffer::UnBind(unsigned int Number)
{
	glActiveTexture(GL_TEXTURE0 + Number);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint MFrameBuffer::GetTextureId()
{
	return TextureId;
}

GLuint MFrameBuffer::GetId()
{
	return Id;
}

void MFrameBuffer::Begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Id);
	glClear(GL_COLOR_BUFFER_BIT);
}

void MFrameBuffer::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void MFrameBuffer::Close()
{
	glDeleteFramebuffers(1, &Id);
	glDeleteTextures(1, &TextureId);
}
