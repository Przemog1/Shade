#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
{
	defaultShader.getSourceCode(Shader::Type::Vertex,   "shaders/BlinnPhongVS.shader");
	defaultShader.getSourceCode(Shader::Type::Fragment, "shaders/BlinnPhongFS.shader");
	defaultShader.linkProgram();
}

ShaderManager::~ShaderManager()
{

}

ShaderManager& ShaderManager::get()
{
	static ShaderManager instance;
	return instance;
}

void ShaderManager::addShader(const std::string& name)
{
	shaders.emplace(std::make_pair(name, Shader()));
}

void ShaderManager::addShader(const std::string& name, Shader&& shader)
{
	shaders.emplace(std::make_pair(name, std::move(shader)));
}

Shader* ShaderManager::getShader(const std::string& name)
{
	auto shader = shaders.find(name);

	if (shader == shaders.end())
	{
		std::cout << "Shader: " << name << " doesn't exist.\n";
		return &defaultShader;
	}

	return &(shader->second);
}

const Shader* ShaderManager::getShader(const std::string& name) const
{
	auto shader = shaders.find(name);

	if (shader == shaders.end())
	{
		std::cout << "Shader: " << name << " doesn't exist.\n";
		return &defaultShader;
	}

	return &(shader->second);
}