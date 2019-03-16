#pragma once
#include <GMath/Matrix/Mat4f.h>
#include <GMath/Vector/Vec3f.h>

class Transformable
{
public:
	void setTransform(const gmath::Mat4f& transformMatrix);

	inline gmath::Mat4f& getTransform() { return transform; }
	inline const gmath::Mat4f& getTransform() const { return transform; }

	void setPosition(float x, float y, float z);
	void setScale(float scalar);
	void setScale(float x, float y, float z);

	/*
	void move(float x, float y, float z);
	void scale(float scalar);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);*/

protected:
	Transformable();
	virtual ~Transformable();

	Transformable(Transformable&&) = default;
	Transformable& operator=(Transformable&&) = default;
	Transformable(const Transformable&) = default;
	Transformable& operator=(const Transformable&) = default;

private:
	/*gmath::Vec3f translationVector;
	gmath::Vec3f rotationVector;*/
	gmath::Mat4f transform;

	
};

