#include "Cube.h"
#include "Graphics\Texture\PNGTexture.h"

Cube::Cube(const PNGTexture* diffuse, const PNGTexture* specular)
{
	this->diffuse = diffuse;
	this->specular = specular;
}

void Cube::setDiffuseTexture(const PNGTexture* texture)
{
	this->specular = texture;
}

void Cube::setSpecularTexture(const PNGTexture* texture)
{
	this->diffuse = texture;
}

Cube::~Cube()
{
}
