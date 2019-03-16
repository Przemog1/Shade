#include "IBO.h"
#include <glad/glad.h>
#include <cstddef>

IBO::IBO()
	:iboID(0)
{

}

IBO::IBO(const unsigned int* indices, unsigned int count)
{
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*count, (void*)indices, GL_STATIC_DRAW);
}

IBO::~IBO()
{
	glDeleteBuffers(1, &iboID);
}

IBO::IBO(IBO&& other) noexcept
{
	iboID = other.iboID;
	other.iboID = 0;
}
IBO& IBO::operator=(IBO&& other) noexcept
{
	iboID = other.iboID;
	other.iboID = 0;

	return *this;
}

void IBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}

void IBO::setData(const unsigned int* indices, unsigned int count)
{
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*count, (void*)indices, GL_STATIC_DRAW);
}