#pragma once
#include "Graphics/Shader/Shader.h"
#include "Graphics/buffers/SSBO.h"
#include "PointLight.h"
#include <vector>

class LightSetup
{
public:
	void addPointLight(const PointLight& pointLightSource);
	void updateSSBOLightingData(SSBO& ssbo) const;

private:
	std::vector<PointLight> pointLights;

};
