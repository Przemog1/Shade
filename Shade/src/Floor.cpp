#include "Floor.h"
#include <GMath/Matrix/Mat4f.h>
#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>
#include <glad/glad.h>

Floor::Floor()
	:diffuse(nullptr), specular(nullptr)
{
	Vertex vertices[] = {
		{-100.0f, -0.5f, -100.0f,	0.0f,   150.0f,	 0.0f, 1.0f, 0.0f},
		{ 100.0f, -0.5f, -100.0f,	150.0f, 150.0f,	 0.0f, 1.0f, 0.0f},
		{ 100.0f, -0.5f,  100.0f,	150.0f, 0.0f,	 0.0f, 1.0f, 0.0f},
		{-100.0f, -0.5f,  100.0f,	0.0f,   0.0f,	 0.0f, 1.0f, 0.0f},
	};

	unsigned int indices[] = {
		2,1,0,
		3,2,0
	};

	vao.bind();

	vbo.setData(vertices, 4);
	ibo.setData(indices, 6);
}

void Floor::setTexture(PNGTexture * texture, TextureType texType)
{
	this->diffuse = texture;
}

void Floor::draw(Shader& shader)
{
	vao.bind();
	shader.uniformMatrix4f("modelMatrix", gmath::Mat4f(1.0f).getMatrixPtr());
	if (diffuse != nullptr)
	{
		shader.uniform1i("tex", 0);
		diffuse->bind();
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}