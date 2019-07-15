#version 330 core

layout(location = 4) in vec3 vertexPosition_modelspace;
layout(location = 5) in vec2 vertexUV;
layout(location = 6) in vec2 vertexOffset;
layout(location = 7) in vec2 uvOffset;

uniform bool useOffsetVertex;
uniform bool useOffsetUV;
uniform mat4 MVP;
out vec2 UV;

void main()
{
	gl_Position =  MVP * vec4(vertexPosition_modelspace + vec3(vertexOffset * float(useOffsetVertex), 0), 1);
	UV = vertexUV + uvOffset * float(useOffsetUV);
}
