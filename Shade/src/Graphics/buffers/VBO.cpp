#include "VBO.h"
#include <glad/glad.h>
#include <cstddef>


VBO::VBO(const Vertex* vertexArray, unsigned int count)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*count, (void*)vertexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::tex_u)) );
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal_x)));
}

VBO::VBO()
	:vboID(0)
{

}

VBO::~VBO()
{
	glDeleteBuffers(1, &vboID);
}

VBO::VBO(VBO&& other) noexcept
{
	vboID = other.vboID;
	other.vboID = 0;
}
VBO& VBO::operator=(VBO&& other) noexcept
{
	vboID = other.vboID;
	other.vboID = 0;

	return *this;
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void VBO::setData(const Vertex* vertexArray, unsigned int count)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*count, (void*)vertexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::tex_u)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal_x)));
}