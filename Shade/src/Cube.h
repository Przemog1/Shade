#pragma once
#include "Transformable.h"
#include "Graphics/Texture/PNGTexture.h"

class Cube : public Transformable
{
public:
	explicit Cube(PNGTexture*texture);
	Cube();
	~Cube();

	void setTexture(PNGTexture* texture);
	inline const PNGTexture* getTexture() const { return texture; }

private:
	PNGTexture* texture;
};

