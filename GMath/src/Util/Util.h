#pragma once

namespace gmath
{
	const float PI = 3.1415926535f;

	constexpr float degToRad(float degrees)
	{
		return degrees / 180.0f * PI;
	}
}
