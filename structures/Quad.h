#ifndef quadH
#define quadH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct stLine
{
	glm::vec2 p[2];
};

struct stRay
{
	glm::vec2 Origin;
    glm::vec2 Direction;
};

struct stQuad
{
	glm::vec2 p[4];
};

struct stUVQuad
{
	glm::vec2 p[4][2];
};

void NullQuad(stQuad& dstQuad);
void SetQuad(stQuad& Quad, float X0, float Y0, float X1, float Y1, float X2, float Y2, float X3, float Y3);
void SetQuad(stQuad& Quad, float StartX, float StartY, float Width, float Height);
void SetQuad(stQuad& Quad, float* p);
void SetQuad(stQuad& Quad, glm::vec2 P0, glm::vec2 P1, glm::vec2 P2, glm::vec2 P3);
void SetQuadBy2Points(stQuad& Quad, float X0, float Y0, float X1, float Y1);
void SetQuadCH(stQuad& Quad, float CenterX, float CenterY, float HalfWidth, float HalfHeight);
void MoveQuad(stQuad& Quad, float X, float Y);
void MoveQuad(stQuad& Quad, glm::vec2 Velocity);
void SetQuadRand(stQuad& Quad, float StartX, float StartY, float Limit, float Min);
void QuadAddEdge(stQuad& Quad, float EdgeSize);
glm::vec2 GetQuadCenter(stQuad Quad);
glm::vec2 GetQuadSize(stQuad Quad);

void NullUVQuad(stUVQuad& Quad);
void SetUVQuad(stUVQuad& Quad, float PX0, float PY0, float PX1, float PY1, float PX2, float PY2, float PX3, float PY3,
	float TX0, float TY0, float TX1, float TY1, float TX2, float TY2, float TX3, float TY3);
void SetUVQuad(stUVQuad& Quad, stQuad Vertex, stQuad UV);
void MoveUVQuad(stUVQuad& UVQuad, float X, float Y);
void MoveUVQuad(stUVQuad& Quad, glm::vec2 Velocity);
stQuad GetVertexQuad(stUVQuad UVQuad);
stQuad GetUVQuad(stUVQuad UVQuad);

#endif
