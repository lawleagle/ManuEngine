#version 330 core

in vec2 UV;
out vec3 color;
uniform sampler2D Texture;

void main()
{
	color = texture(Texture, UV).rgb;
}