#pragma once
#include "Graphics/Texture/PNGTexture.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/buffers/Buffers.h"

class Floor
{
public:
	Floor();

	void setDiffuseTexture(const PNGTexture * texture);
	void setSpecularTexture(const PNGTexture * texture);
	void draw(Shader& shader);

	inline const PNGTexture*  getDiffuseTexture()	{ return diffuse; }
	inline const PNGTexture*  getSpecularTexture() { return specular; }

private:
	const PNGTexture* diffuse;
	const PNGTexture* specular;

	VAO vao;
	VBO vbo;
	IBO ibo;
};
