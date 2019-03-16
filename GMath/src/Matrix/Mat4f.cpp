#include "..\..\include\GMath\Matrix\Mat4f.h"
#include "..\..\include\GMath\Vector\Vec3f.h"
#include "..\..\include\GMath\Vector\Vec4f.h"
#include <memory>
#include <iostream>
#include <iomanip>

namespace gmath
{
	Mat4f::Mat4f()
	{
		std::memset(&matrix[0][0], 0, 16 * sizeof(float));
	}

	Mat4f::Mat4f(float diagonal)
	{
		std::memset(&matrix[0][0], 0, 16 * sizeof(float));
		matrix[0][0] = diagonal;
		matrix[1][1] = diagonal;
		matrix[2][2] = diagonal;
		matrix[3][3] = diagonal;
	}

	Mat4f& Mat4f::operator*=(const Mat4f& other)
	{
		Mat4f result;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				result(i, j) = matrix[i][0] * other(0, j) + matrix[i][1] * other(1, j) +
					matrix[i][2] * other(2, j) + matrix[i][3] * other(3, j);
			}

		memcpy(&matrix[0][0], result.getMatrixPtr(), 16 * sizeof(float));

		return *this;
	}

	Mat4f& Mat4f::inverse() { return *this; }

	Vec4f Mat4f::getTranslation4f() const
	{
		return Vec4f(matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
	}
	Vec3f Mat4f::getTranslation3f() const
	{
		return { matrix[0][3], matrix[1][3], matrix[2][3] };
	}
	void Mat4f::setTranslation(float x, float y, float z)
	{
		matrix[0][3] = x;
		matrix[1][3] = y;
		matrix[2][3] = z;
	}
	void Mat4f::setTranslation(const Vec3f& vec)
	{
		matrix[0][3] = vec.x;
		matrix[1][3] = vec.y;
		matrix[2][3] = vec.z;
	}

	float* Mat4f::getMatrixPtr() { return &matrix[0][0]; }

	void Mat4f::print() const
	{
		for (int i = 0; i < 4; i++)
			std::cout << std::setw(5) <<  matrix[i][0] << ' ' << std::setw(5) << matrix[i][1] << ' '
			<< std::setw(5) << matrix[i][2] << ' ' << std::setw(5) << matrix[i][3] << '\n';

		std::cout << '\n';
	}
}