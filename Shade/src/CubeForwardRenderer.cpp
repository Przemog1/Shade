#include "CubeForwardRenderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>

CubeForwardRenderer::CubeForwardRenderer()
{
	Vertex vertices[] = {
		{-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},  // 0  //	left bot near		FRONT
		{ 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 1  //	right bot near
		{ 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},  // 2  //	right top near
		{-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},  // 3  //	left top near

	    {-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 4  //	left bot far		BACK
		{ 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 5  //	right bot far
		{ 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 6  //	right top far
	    {-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 7  //	left top far

		{ 0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 8  //	right bot near		RIGHT
		{ 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 9  //	right bot far
		{ 0.5f,  0.5f,  0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},  // 10 //	right top near
		{ 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 11 //	right top far

		{-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 12 //	left bot far		LEFT
		{-0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},  // 13 //	left bot near
		{-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 14 //	left top far
		{-0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},  // 15 //	left top near

		{-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},  // 16  //	left top near		TOP
		{ 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},  // 17 //	right top near
		{-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 18 //	left top far
		{ 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 19 //	right top far
		
		{-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f},  // 20 //	left bot near		BOTTOM
		{ 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f},	// 21 //	right bot near
		{ 0.5f, -0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 22 //	right bot far
		{-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f},	// 23 //	left bot far
	};
	
	unsigned int indices[] = {
		0, 1, 2,	0, 2, 3, 	//front
		6, 5, 4,    7, 6, 4,	//back
		8, 9, 10,    9, 11, 10,	//right
		12, 13, 14,    14, 13, 15,	//left
		16, 17, 18,    19, 18, 17,	//top
		22, 21, 20,    23, 22, 20	//bottom
	};

	vao.bind();
	vbo.setData(vertices, 24);
	ibo.setData(indices, 36);
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
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

void CubeForwardRenderer::drawMultiple(const std::vector<Cube>& cubes, Shader& shader)
{

}