#pragma once

namespace gmath
{
	struct Vec2f
	{
		float x;
		float y;

		Vec2f();
		explicit Vec2f(float s);
		Vec2f(float x, float y);

		Vec2f& operator+=(const Vec2f& other);
		Vec2f& operator-=(const Vec2f& other);
		Vec2f& operator*=(float scalar);

		Vec2f& normalize();

		float getLength() const;

		void print() const;
	};
}