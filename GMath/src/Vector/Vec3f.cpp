#include "..\..\include\GMath\Vector\Vec3f.h"
#include <iostream>

namespace gmath
{

	Vec3f::Vec3f()
		:x(0.0f), y(0.0f), z(0.0f) {};

	Vec3f::Vec3f(float s)
		:x(s), y(s), z(s) {};

	Vec3f::Vec3f(float x, float y, float z)
		:x(x), y(y), z(z) {};

	Vec3f& Vec3f::operator+=(const Vec3f& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec3f& Vec3f::operator-=(const Vec3f& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec3f& Vec3f::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vec3f& Vec3f::normalize()
	{
		float length = sqrt(x*x + y * y);

		if (length == 0.0f)
			return *this;

		x /= length;
		y /= length;

		return *this;
	}

	float Vec3f::getLength() const
	{
		return sqrt(x*x + y * y + z*z);
	}

	void Vec3f::print() const
	{
		std::cout << x << ' ' << y << ' ' << z << '\n';
	}
}

