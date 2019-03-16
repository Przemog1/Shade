#pragma once
#include "../Application.h"
#include "../Graphics/Texture/PNGTexture.h"

#include "../Graphics/TextureManager/TextureManager.h"
#include "../Graphics/buffers/Buffers.h"
#include "../Graphics/Shader/Shader.h"
#include <GMath/Matrix.h>
#include <glad/glad.h>
#include "../CubeForwardRenderer.h"
#include "../Util/Timer.h"
#include "../Camera.h"
#include "../Floor.h"
#include "../Graphics/Shader/Shader.h"

#include <iostream>


class PNGTexture;
class Sandbox : public Application
{
public:
	Sandbox(int windowWidth, int windowHeight, const std::string& title);
	~Sandbox();

private:
	void onStart() override;
	void update() override;

private:
	PNGTexture* texture;
	Cube cube;
	CubeForwardRenderer& cubeRenderer;
	Timer timer;
	Camera camera;
	gmath::Mat4f perspectiveMatrix;

	Floor floor;
	
	Shader shader;

private:
	void updateTimer();
	float timeElapsed;
	float deltaTime;

private:
	void initializeShader();

};

Application* createApplication()
{
	return new Sandbox(960,540,"Hello!");
}

