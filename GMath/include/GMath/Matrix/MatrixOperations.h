#pragma once


namespace gmath
{
	struct Vec4f;
	class Mat4f;

	Mat4f operator*(const Mat4f& lhs, const Mat4f& rhs);

	Vec4f operator*(const Mat4f& lhs, const Vec4f& rhs);
}
