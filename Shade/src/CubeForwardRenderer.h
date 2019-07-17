#include "Cube.h"
#include <vector>
#include "Graphics/Shader/Shader.h"
#include "Graphics/buffers/Buffers.h"
#include "Camera.h"

#include <iostream>

class CubeForwardRenderer
{
public:
	CubeForwardRenderer();
	~CubeForwardRenderer();

	void draw(Cube& cube, Shader& shader);
	void drawMultiple(const std::vector<Cube>& cubes, Shader& shader);

private:
	CubeForwardRenderer(const CubeForwardRenderer&) = delete;
	CubeForwardRenderer& operator=(const CubeForwardRenderer&) = delete;

	VAO vao;
	VBO vbo;
	IBO ibo;
};