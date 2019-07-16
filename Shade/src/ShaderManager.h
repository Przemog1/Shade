#pragma once
#include <unordered_map>
#include "Graphics/Shader/Shader.h"
#include <string>

class ShaderManager
{
public:
	static ShaderManager& get();

	//after construction shader is not compiled yet, it is required to add source code and compile it manually
	void addShader(const std::string& name);

	//move from existing shader
	void addShader(const std::string& name, Shader&& shader);

	Shader* getShader(const std::string& name);
	const Shader* getShader(const std::string& name) const;
private:
	ShaderManager();
	~ShaderManager();

	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

	std::unordered_map<std::string, Shader> shaders;

	Shader defaultShader;
};
