#include "LightSetup.h"
#include <iostream>

void LightSetup::addPointLight(const PointLight& pointLightSource)
{
	pointLights.push_back(pointLightSource);
}

void LightSetup::updateSSBOLightingData(SSBO& ssbo) const
{
	const size_t bufferSize = pointLights.size() * sizeof(PointLight) + sizeof(unsigned int) * 4;
	std::unique_ptr<uint8_t[]> data(new uint8_t[bufferSize]);

	//first component of PointLightBuffer is uint (number of lights)
	*( (unsigned int*)(data.get()) ) = pointLights.size();

	const size_t firstLightOffset = reinterpret_cast<size_t>(data.get()) + (sizeof(unsigned int) * 4);

	for (unsigned int i = 0; i < pointLights.size(); i++)
	{
		size_t lightOffset = firstLightOffset + i * sizeof(PointLight);
		std::memcpy(reinterpret_cast<void*>(lightOffset), &pointLights[i], sizeof(PointLight));
	}

	ssbo.bind();
	ssbo.setData((void*)data.get(), bufferSize);
}
