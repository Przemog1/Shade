#pragma once
#include "Transformable.h"
#include "Graphics/Texture/PNGTexture.h"

class Cube : public Transformable
{
public:
	explicit Cube(const PNGTexture* diffuse = nullptr, const PNGTexture* specular = nullptr);
	~Cube();

	void setDiffuseTexture(const PNGTexture* texture);
	void setSpecularTexture(const PNGTexture* texture);
	inline const PNGTexture* getDiffuseTexture() const { return diffuse; }
	inline const PNGTexture* getSpecularTexture() const { return specular; }


private:
	const PNGTexture* diffuse;
	const PNGTexture* specular;
};

