#version 450 core

in vec2 f_texCoords;
out vec4 outputColor;

uniform sampler2D tex;

void main()
{
	outputColor = texture(tex, f_texCoords);
}