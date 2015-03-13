#version 330 core

uniform mat4 CameraMatrix;
uniform mat4 ModelMatrix;
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
out vec2 uv;


void main()
{
	gl_Position = CameraMatrix * ModelMatrix * vec4(vertexPosition, 1);
	uv = vertexUV;
}