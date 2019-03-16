#include "CubeForwardRenderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>

CubeForwardRenderer::CubeForwardRenderer()
{
	Vertex vertices[] = {
	   {-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, -0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},

	   {-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},

	   {-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},

		{0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},

	   {-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	   
	   {-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
		{0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},
	   {-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},
	};
		
	vao.bind();
	vbo.setData(vertices, 36);
}

CubeForwardRenderer::~CubeForwardRenderer()
{

}

CubeForwardRenderer& CubeForwardRenderer::get()
{
	static CubeForwardRenderer instance;
	return instance;
}


void CubeForwardRenderer::draw(/*FIX IT!*/ Cube& cube,/*FIX IT!*/ Shader& shader)
{
	shader.bind();
	vao.bind();

	cube.getTexture()->bind();
	shader.uniform1i("tex", 0);
	shader.uniformMatrix4f("modelMatrix", cube.getTransform().getMatrixPtr());
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeForwardRenderer::drawMultiple(const std::vector<Cube>& cubes, Shader& shader)
{

}