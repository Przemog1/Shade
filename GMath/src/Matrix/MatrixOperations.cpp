#include "..\..\include\GMath\Matrix\MatrixOperations.h"
#include "..\..\include\GMath\Vector\Vec4f.h"
#include "..\..\include\GMath\Matrix\Mat4f.h"

namespace gmath
{
	Mat4f operator*(const Mat4f& lhs, const Mat4f& rhs)
	{
		Mat4f result;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				result(i, j) = lhs(i, 0) * rhs(0, j) + lhs(i, 1) * rhs(1, j) +
					lhs(i, 2) * rhs(2, j) + lhs(i, 3) * rhs(3, j);
			}

		return result;
	}

	Vec4f operator*(const Mat4f& lhs, const Vec4f& rhs)
	{
		Vec4f result;

		result.x = lhs(0, 0) * rhs.x + lhs(0, 1) * rhs.y + lhs(0, 2) * rhs.z + lhs(0, 3) * rhs.w;
		result.y = lhs(1, 0) * rhs.x + lhs(1, 1) * rhs.y + lhs(1, 2) * rhs.z + lhs(1, 3) * rhs.w;
		result.z = lhs(2, 0) * rhs.x + lhs(2, 1) * rhs.y + lhs(2, 2) * rhs.z + lhs(2, 3) * rhs.w;
		result.w = lhs(3, 0) * rhs.x + lhs(3, 1) * rhs.y + lhs(3, 2) * rhs.z + lhs(3, 3) * rhs.w;

		return result;
	}
}