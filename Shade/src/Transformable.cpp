#include "Transformable.h"



Transformable::Transformable()
	:transform(1.0f)
{
}


Transformable::~Transformable()
{
}

void Transformable::setTransform(const gmath::Mat4f& transformMatrix)
{
	transform = transformMatrix;
}

void Transformable::setPosition(float x, float y, float z)
{
	transform.setTranslation(x, y, z);
}

void Transformable::setScale(float scalar)
{
	transform(0, 0) = scalar;
	transform(1, 1) = scalar;
	transform(2, 2) = scalar;
}

void Transformable::setScale(float x, float y, float z)
{
	transform(0, 0) = x;
	transform(1, 1) = y;
	transform(2, 2) = z;
}