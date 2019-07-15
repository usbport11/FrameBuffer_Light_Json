#include "Quad.h"

void NullQuad(stQuad& Quad)
{
	Quad.p[0] = glm::vec2(0, 0);
	Quad.p[1] = glm::vec2(0, 0);
	Quad.p[2] = glm::vec2(0, 0);
	Quad.p[3] = glm::vec2(0, 0);
}

void SetQuad(stQuad& Quad, float X0, float Y0, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	Quad.p[0] = glm::vec2(X0, Y0);
	Quad.p[1] = glm::vec2(X1, Y1);
	Quad.p[2] = glm::vec2(X2, Y2);
	Quad.p[3] = glm::vec2(X3, Y3);
}

void SetQuad(stQuad& Quad, float StartX, float StartY, float Width, float Height)
{
	Quad.p[0] = glm::vec2(StartX, StartY);
	Quad.p[1] = glm::vec2(StartX, StartY + Height);
	Quad.p[2] = glm::vec2(StartX + Width, StartY + Height);
	Quad.p[3] = glm::vec2(StartX + Width, StartY);
}

void SetQuad(stQuad& Quad, float* p)
{
	if(!p) return;
	Quad.p[0] = glm::vec2(*p, *(p+1));
	Quad.p[1] = glm::vec2(*(p+2), *(p+3));
	Quad.p[2] = glm::vec2(*(p+4), *(p+5));
	Quad.p[3] = glm::vec2(*(p+6), *(p+7));
}

void SetQuad(stQuad& Quad, glm::vec2 P0, glm::vec2 P1, glm::vec2 P2, glm::vec2 P3)
{
	Quad.p[0] = P0;
	Quad.p[1] = P1;
	Quad.p[2] = P2;
	Quad.p[3] = P3;
}

void SetQuadCH(stQuad& Quad, float CenterX, float CenterY, float HalfWidth, float HalfHeight)
{
	Quad.p[0] = glm::vec2(CenterX - HalfWidth, CenterY - HalfHeight);
	Quad.p[1] = glm::vec2(CenterX - HalfWidth, CenterY + HalfHeight);
	Quad.p[2] = glm::vec2(CenterX + HalfWidth, CenterY + HalfHeight);
	Quad.p[3] = glm::vec2(CenterX + HalfWidth, CenterY - HalfHeight);
}

void SetQuadBy2Points(stQuad& Quad, float X0, float Y0, float X1, float Y1)
{
	Quad.p[0] = glm::vec2(X0, Y0);
	Quad.p[1] = glm::vec2(X0, Y1);
	Quad.p[2] = glm::vec2(X1, Y1);
	Quad.p[3] = glm::vec2(X1, Y0);
}

void MoveQuad(stQuad& Quad, float X, float Y)
{
	Quad.p[0] += glm::vec2(X, Y);
	Quad.p[1] += glm::vec2(X, Y);
	Quad.p[2] += glm::vec2(X, Y);
	Quad.p[3] += glm::vec2(X, Y);
}

void MoveQuad(stQuad& Quad, glm::vec2 Velocity)
{
	Quad.p[0] += Velocity;
	Quad.p[1] += Velocity;
	Quad.p[2] += Velocity;
	Quad.p[3] += Velocity;
}

void SetQuadRand(stQuad& Quad, float StartX, float StartY, float Limit, float Min)
{
	float randVal = rand() % ((int)Limit - (int)Min) + Min;
	Quad.p[0] = glm::vec2(StartX, StartY);
	Quad.p[1] = glm::vec2(StartX, StartY + randVal);
	Quad.p[2] = glm::vec2(StartX + randVal, StartY + randVal);
	Quad.p[3] = glm::vec2(StartX + randVal, StartY);
}

void QuadAddEdge(stQuad& Quad, float EdgeSize)
{
	Quad.p[0] = glm::vec2(Quad.p[0].x - EdgeSize, Quad.p[0].y - EdgeSize);
	Quad.p[1] = glm::vec2(Quad.p[1].x - EdgeSize, Quad.p[1].y + EdgeSize);
	Quad.p[2] = glm::vec2(Quad.p[2].x + EdgeSize, Quad.p[2].y + EdgeSize);
	Quad.p[3] = glm::vec2(Quad.p[3].x + EdgeSize, Quad.p[3].y - EdgeSize);
}

glm::vec2 GetQuadCenter(stQuad Quad)
{
	return glm::vec2((Quad.p[3].x - Quad.p[0].x) / 2 + Quad.p[0].x, (Quad.p[1].y - Quad.p[0].y) / 2 + Quad.p[0].y);
}

glm::vec2 GetQuadSize(stQuad Quad)
{
	return glm::vec2(Quad.p[3].x - Quad.p[0].x, Quad.p[1].y - Quad.p[0].y);
}

void NullUVQuad(stUVQuad& Quad)
{
	Quad.p[0][1] = Quad.p[0][0] = glm::vec2(0, 0);
	Quad.p[1][1] = Quad.p[1][0] = glm::vec2(0, 0);
	Quad.p[2][1] = Quad.p[2][0] = glm::vec2(0, 0);
	Quad.p[3][1] = Quad.p[3][0] = glm::vec2(0, 0);
}

void SetUVQuad(stUVQuad& Quad, float PX0, float PY0, float PX1, float PY1, float PX2, float PY2, float PX3, float PY3,
	float TX0, float TY0, float TX1, float TY1, float TX2, float TY2, float TX3, float TY3)
{
	Quad.p[0][0] = glm::vec2(PX0, PY0);
	Quad.p[0][1] = glm::vec2(TX0, TY0);
	Quad.p[1][0] = glm::vec2(PX1, PY1);
	Quad.p[1][1] = glm::vec2(TX1, TY1);
	Quad.p[2][0] = glm::vec2(PX2, PY2);
	Quad.p[2][1] = glm::vec2(TX2, TY2);
	Quad.p[3][0] = glm::vec2(PX3, PY3);
	Quad.p[3][1] = glm::vec2(TX3, TY3);
}

void SetUVQuad(stUVQuad& Quad, stQuad Vertex, stQuad UV)
{
	Quad.p[0][0] = Vertex.p[0];
	Quad.p[0][1] = UV.p[0];
	Quad.p[1][0] = Vertex.p[1];
	Quad.p[1][1] = UV.p[1];
	Quad.p[2][0] = Vertex.p[2];
	Quad.p[2][1] = UV.p[2];
	Quad.p[3][0] = Vertex.p[3];
	Quad.p[3][1] = UV.p[3];
}

void MoveUVQuad(stUVQuad& UVQuad, float X, float Y)
{
	UVQuad.p[0][0] += glm::vec2(X, Y);
	UVQuad.p[1][0] += glm::vec2(X, Y);
	UVQuad.p[2][0] += glm::vec2(X, Y);
	UVQuad.p[3][0] += glm::vec2(X, Y);
}

void MoveUVQuad(stUVQuad& UVQuad, glm::vec2 Velocity)
{
	UVQuad.p[0][0] += Velocity;
	UVQuad.p[1][0] += Velocity;
	UVQuad.p[2][0] += Velocity;
	UVQuad.p[3][0] += Velocity;
}

stQuad GetVertexQuad(stUVQuad UVQuad)
{
	stQuad Quad;
	
	Quad.p[0] = UVQuad.p[0][0];
	Quad.p[1] = UVQuad.p[1][0];
	Quad.p[2] = UVQuad.p[2][0];
	Quad.p[3] = UVQuad.p[3][0];
	
	return Quad;
}

stQuad GetUVQuad(stUVQuad UVQuad)
{
	stQuad Quad;
	
	Quad.p[0] = UVQuad.p[0][1];
	Quad.p[1] = UVQuad.p[1][1];
	Quad.p[2] = UVQuad.p[2][1];
	Quad.p[3] = UVQuad.p[3][1];
	
	return Quad;
}
