#include "..\..\include\GMath\Vector\Vec2f.h"
#include <iostream>

namespace gmath
{

	Vec2f::Vec2f()
		:x(0.0f), y(0.0f) {};

	Vec2f::Vec2f(float s)
		:x(s), y(s) {};

	Vec2f::Vec2f(float x, float y)
		:x(x), y(y) {};

	Vec2f& Vec2f::operator+=(const Vec2f& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2f& Vec2f::operator-=(const Vec2f& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2f& Vec2f::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vec2f& Vec2f::normalize()
	{
		float length = sqrt(x*x + y * y);

		if (length == 0.0f)
			return *this;

		x /= length;
		y /= length;

		return *this;
	}

	float Vec2f::getLength() const
	{
		return sqrt(x*x + y * y);
	}

	void Vec2f::print() const
	{
		std::cout << x << ' ' << y << '\n';
	}
}

