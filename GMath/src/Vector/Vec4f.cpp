#include "..\..\include\GMath\Vector\Vec2f.h"
#include "..\..\include\GMath\Vector\Vec3f.h"
#include "..\..\include\GMath\Vector\Vec4f.h"
#include <iostream>

namespace gmath
{

	Vec4f::Vec4f()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};

	Vec4f::Vec4f(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w) {};

	Vec4f::Vec4f(const Vec2f& vec, float z, float w)
		:z(z), w(w)
	{
		x = vec.x;
		y = vec.y;
	}
	Vec4f::Vec4f(const Vec3f& vec, float w )
		:w(w)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	void Vec4f::print() const
	{
		std::cout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
	}
}

