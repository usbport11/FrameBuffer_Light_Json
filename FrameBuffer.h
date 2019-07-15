#ifndef framebufferH
#define framebufferH

class MFrameBuffer
{
private:
	GLuint Id;
	GLuint TextureId;
	unsigned int Width;
	unsigned int Height;
	GLint Parameters[4];
	GLint ImageFormat;
	GLenum Format;
public:
	MFrameBuffer();
	bool SetParameters(GLint inImageFormat, GLenum inFormat, GLint MagF, GLint MinF, GLint WrapS, GLint WrapT);
	bool Initialize(unsigned int inWidth, unsigned int inHeight);
	void Bind(unsigned int Number);
	void UnBind(unsigned int Number);
	GLuint GetTextureId();
	GLuint GetId();
	void Begin();
	void End();
	void Close();
};

#endif
