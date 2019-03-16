#pragma once
#include "Graphics/Texture/PNGTexture.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/buffers/Buffers.h"

class Floor
{
public:
	Floor();

	void setTexture(PNGTexture * texture, TextureType texType);
	void draw(Shader& shader);

private:
	PNGTexture* diffuse;
	PNGTexture* specular;

	VAO vao;
	VBO vbo;
	IBO ibo;
};
