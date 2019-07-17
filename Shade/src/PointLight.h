#pragma once

#include "LightSource.h"
#include <GMath/Vector.h>

struct PointLight
{
	gmath::Vec4f pos;
	gmath::Vec4f ambientColor;
	gmath::Vec4f diffuseColor;
	gmath::Vec4f specularColor;
};
