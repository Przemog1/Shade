#include "VAO.h"
#include <glad/glad.h>
#include <cstddef>


VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void VAO::bind() const
{
	glBindVertexArray(vaoID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

VAO::VAO(VAO&& other) noexcept
{
	vaoID = other.vaoID;
	other.vaoID = 0;
}
VAO& VAO::operator=(VAO&& other) noexcept
{
	vaoID = other.vaoID;
	other.vaoID = 0;

	return *this;
}