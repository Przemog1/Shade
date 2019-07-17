#pragma once
#include <string>
#include <unordered_map>
#include <GMath/Vector.h>

class Shader
{
public:
	Shader();
	~Shader();

	enum class Type { Vertex, Fragment };
	void getSourceCode(Shader::Type type, const std::string& fileName);

	void linkProgram();

	void bind() const;
	void unbind() const;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
		
	//uniforms
public:
	void uniform1f(const std::string& uniformName, float v);
	void uniform3f(const std::string& uniformName, float x, float y, float z);
	void uniform3f(const std::string& uniformName, gmath::Vec3f vec);
	void uniform1i(const std::string& uniformName, int v);
	void uniformMatrix4f(const std::string& uniformName, float* matrixPtr);

	//temporary
	inline unsigned int getShaderProgramID() { return shaderProgramID; }
private:
	unsigned int shaderProgramID;
	std::unordered_map<std::string, int> uniforms;

	int findUniform(const std::string& uniformName);
};