#version 330 core


uniform mat4 CameraMatrix;
uniform mat4 ModelMatrix;
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal;
out vec2 uv;
out vec3 normal;


void main()
{

	gl_Position = CameraMatrix * ModelMatrix * vec4(vertexPosition, 1);
	uv = vertexUV;
	normal = normalize((ModelMatrix * vec4(vertexNormal, 0)).xyz);
}