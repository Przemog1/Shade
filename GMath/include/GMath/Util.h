#pragma once

namespace gmath
{
	const double PI = 3.141592653589793238463;
	const float  PI_F = 3.14159265358979f;

	constexpr float degToRad(float degrees)
	{
		return  (degrees * PI_F) / 180.0f;
	}
}


