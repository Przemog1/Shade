#include "Cube.h"
#include <vector>
#include "Graphics/Shader/Shader.h"
#include "Graphics/buffers/Buffers.h"
#include "Camera.h"

#include <iostream>

class CubeForwardRenderer
{
public:
	void draw(Cube& cube, Shader& shader);
	void drawMultiple(const std::vector<Cube>& cubes, Shader& shader);

	static CubeForwardRenderer& get();
private:
	CubeForwardRenderer();
	~CubeForwardRenderer();

	CubeForwardRenderer(const CubeForwardRenderer&) = delete;
	CubeForwardRenderer& operator=(const CubeForwardRenderer&) = delete;

	VAO vao;
	VBO vbo;
	IBO ibo;
};