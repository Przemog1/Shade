#include "Cube.h"
#include "Graphics\Texture\PNGTexture.h"

Cube::Cube()
	:texture(nullptr)
{
}

Cube::Cube(PNGTexture* texture)
{
	this->texture = texture;
}

void Cube::setTexture(PNGTexture* texture)
{
	this->texture = texture;
}


Cube::~Cube()
{
}
