#pragma once
#include "Graphics/Shader/Shader.h"

class LightSource
{
public:
	enum class Type
	{
		pointLight
	};

public:
	virtual LightSource::Type getType() const = 0;
	virtual ~LightSource() = default;

private:
	friend class LightSetup;
	virtual void addToShader(Shader* shader, int lightIndex) const = 0;
};
