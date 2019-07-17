#include "SSBO.h"
#include <glad/glad.h>
#include <cstddef>

SSBO::SSBO(unsigned int binding)
{
	glGenBuffers(1, &SSBOID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, SSBOID);
}

SSBO::~SSBO() noexcept
{
	glDeleteBuffers(1, &SSBOID);
}

SSBO::SSBO(SSBO&& other) noexcept
{
	SSBOID = other.SSBOID;
	other.SSBOID = 0;
}

SSBO& SSBO::operator=(SSBO&& other) noexcept
{
	SSBOID = other.SSBOID;
	other.SSBOID = 0;

	return *this;
}

void SSBO::bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
}

void SSBO::bind(unsigned int binding) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, SSBOID);
}

void SSBO::setData(const void* data, unsigned int dataSize)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, dataSize, data, GL_STATIC_DRAW);
}