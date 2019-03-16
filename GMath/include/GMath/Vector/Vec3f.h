#pragma once

namespace gmath
{
	struct Vec3f
	{
		float x;
		float y;
		float z;

		Vec3f();
		explicit Vec3f(float s);
		Vec3f(float x, float y, float z);

		Vec3f& operator+=(const Vec3f& other);
		Vec3f& operator-=(const Vec3f& other);
		Vec3f& operator*=(float scalar);

		Vec3f& normalize();

		float getLength() const;

		void print() const;
	};
}

