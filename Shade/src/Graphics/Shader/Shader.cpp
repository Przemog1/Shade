#include "Shader.h"
#include <glad/glad.h>
#include <cstdio>
#include <iostream>

Shader::Shader()
	:shaderProgramID(0), isBound(false)
{
	shaderProgramID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgramID);
}

void Shader::getSourceCode(Shader::Type type, const std::string& fileName)
{
	FILE* file = NULL;

	errno_t errCode = 0;
	errCode = fopen_s(&file, fileName.c_str(), "rb");

	if(errCode)
	{
		std::string errMsg("Cannot open ");
		errMsg += fileName;
		std::perror(errMsg.c_str());
		__debugbreak();
		return;
	}


		//set file position indicator at the end
	std::fseek(file, 0, SEEK_END);
	int fileSize = std::ftell(file);

	char* sourceCodeBuffer = new char[fileSize + 1];

		//set file position indicator at beginning
	std::fseek(file, 0, SEEK_SET);

		//load from file to buffer
	for(int i = 0; i < fileSize; i++)
		sourceCodeBuffer[i] = (char)getc(file);
		
		//append NULL at the end of the buffer
	sourceCodeBuffer[fileSize] = 0;

	fclose(file);

		//shader compilation
	unsigned int shaderType = NULL;

	switch (type)
	{
	case Shader::Type::Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;
	case Shader::Type::Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	default:
		std::cout << "unknown shader type\n";
		__debugbreak();
	}

	unsigned int shader = glCreateShader(shaderType);
	
	glShaderSource(shader, 1, &sourceCodeBuffer, NULL);
	glCompileShader(shader);



	{
		int compileStatusFlag = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatusFlag);
		if (compileStatusFlag != GL_TRUE)
		{
			int infoLogLength;
			char* infoLog;
			
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			infoLog = new char[infoLogLength];

			glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog);

			if (type == Shader::Type::Vertex)
				std::cout << "Vertex shader compilation error:\n";
			if (type == Shader::Type::Fragment)
				std::cout << "Fragment shader compilation error:\n";

			glGetShaderInfoLog(shader, 512, 0, infoLog);
			std::cout << infoLog;

			__debugbreak();

			delete[] infoLog;
		}
	}

	glAttachShader(shaderProgramID, shader);

	delete[] sourceCodeBuffer;
	glDeleteShader(shader);
}

void Shader::linkProgram()
{
	char infoLog[512];

	glLinkProgram(shaderProgramID);
	glValidateProgram(shaderProgramID);

	int success;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << infoLog;
	}
}

void Shader::bind() const
{
	glUseProgram(shaderProgramID);
}
void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::uniform1f(const std::string& uniformName, float v)
{
	auto un = uniforms.find(uniformName);

	if (un == uniforms.end())
	{
		un = uniforms.emplace(std::make_pair(uniformName, findUniform(uniformName) )).first;
		glUniform1f(un->second, v);
	}
	else
	{
		glUniform1f(un->second, v);
	}
}

void Shader::uniform3f(const std::string& uniformName, float x, float y, float z)
{
	auto un = uniforms.find(uniformName);

	if (un == uniforms.end())
	{
		un = uniforms.emplace(std::make_pair(uniformName, findUniform(uniformName))).first;
		glUniform3f(un->second, x, y, z);
	}
	else
	{
		glUniform3f(un->second, x, y, z);
	}
}

void Shader::uniform1i(const std::string& uniformName, int v)
{
	auto un = uniforms.find(uniformName);

	if (un == uniforms.end())
	{
		un = uniforms.emplace(std::make_pair(uniformName, findUniform(uniformName))).first;
		glUniform1i(un->second, v);
	}
	else
	{
		glUniform1i(un->second, v);
	}
}

void Shader::uniformMatrix4f(const std::string& uniformName, float* matrixPtr)
{
	auto un = uniforms.find(uniformName);

	if (un == uniforms.end())
	{
		un = uniforms.emplace(std::make_pair(uniformName, findUniform(uniformName))).first;
		glUniformMatrix4fv(un->second, 1, GL_TRUE, matrixPtr);
	}
	else
	{
		glUniformMatrix4fv(un->second, 1, GL_TRUE, matrixPtr);
	}
}

int Shader::findUniform(const std::string& uniformName)
{
	return glGetUniformLocation(shaderProgramID, uniformName.c_str());
}