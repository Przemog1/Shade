#pragma once

namespace gmath
{
	struct Vec2f;
	struct Vec3f;

	struct Vec4f
	{
		float x;
		float y;
		float z;
		float w;

		Vec4f();
		Vec4f(const Vec2f& vec, float z, float w = 1);
		Vec4f(const Vec3f& vec, float w = 1);
		Vec4f(float x, float y, float z, float w = 1);

		

			//w coordinate stays unaffected
		//Vec4f& operator+=(const Vec4f& other);
		//	//w coordinate stays unaffected
		//Vec4f& operator-=(const Vec4f& other);
		//	//w coordinate stays unaffected
		//Vec4f& operator*=(float scalar);

		//Vec4f& normalize();

		//float getLength();

		void print() const;
	};
}
