#pragma once
#include "MatrixOperations.h"
#include "Mat4f.h"
#include "..\Vector\Vec3f.h"

namespace gmath
{
	Mat4f translate(float x, float y, float z);

	Mat4f translate(const Vec3f& vec);
	
	Mat4f rotateX(float radians);

	Mat4f rotateY(float radians);

	Mat4f rotateZ(float radians);

	Mat4f scale(float scalar);

	Mat4f scale(float x, float y, float z);

	Mat4f lookAt(const gmath::Vec3f& from, const gmath::Vec3f& to, const gmath::Vec3f& up = { 0.0f,1.0f,0.0f });
		 
	Mat4f ortho(float left, float right, float bottom, float top, float near, float far);

	Mat4f perspective(float FOV, float aspectRatio, float near, float far);
}