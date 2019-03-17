#include "Sandbox.h"

#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>

//TODO: refactorize shader, window, CubeForwardRenderer class 
//TODO: extend Timer class (timeElapsed and deltaTime needs to be encapsulated)
//TODO: fix (redesign?) the camera class

#include "../Cube.h"
#include <vector>
#include <GLFW/glfw3.h>

Sandbox::Sandbox(int windowWidth, int windowHeight, const std::string& title)
	:Application(windowWidth,windowHeight,title), 
	cubeRenderer(CubeForwardRenderer::get()), 
	camera(gmath::Vec3f(0.0f,0.0,0.0), gmath::Vec3f(0.0,2.0f,-1.0f)),
	timeElapsed(0)
{
	
}

Sandbox::~Sandbox()
{

}

void Sandbox::onStart()
{
	window.setClearColor(0, 123, 123);
	window.enableDepthTest();

	TextureManager::getTextureManager().addTexture("res/textures/pepe.png", "pepe");
	TextureManager::getTextureManager().addTexture("res/textures/wooden_floor/wooden_floor_diffuse.png", "woodenFloor");
	TextureManager::getTextureManager().addTexture("res/textures/metal_diffuse.png", "metal");

	cubes.reserve(15);
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("pepe"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));
	cubes.emplace_back(TextureManager::getTextureManager().getTexture("metal"));

	for (int i = 2; i < cubes.size(); i++)
		cubes[i].setTransform(gmath::translate(0.0f,(float)i - 2.0f,(float)i));


	floor.setTexture(TextureManager::getTextureManager().getTexture("woodenFloor"), TextureType::diffuse);

	initializeShader();

	perspectiveMatrix = gmath::perspective(90.0f, 16.0f / 9.0f, 0.01f, 100.0f);
	shader.uniformMatrix4f("perspectiveMatrix", perspectiveMatrix.getMatrixPtr());


	timer.reset();
}

void Sandbox::update()
{
	updateTimer();
	camera.update(getWindow(), deltaTime);
	if (getWindow().isKeyPressed(GLFW_KEY_ESCAPE))
		window.close();

	//Shader setup
	gmath::Mat4f viewMatrix = camera.getViewMatrix();
	shader.uniformMatrix4f("cameraMatrix", viewMatrix.getMatrixPtr());



	//cube update
	gmath::Mat4f modelMatrix = gmath::translate(0.0f, 0.0f, -2.0f) * gmath::rotateY(timeElapsed * 3.1415926535f / 4.0f);
	cubes[0].setTransform(modelMatrix);
	cubes[1].setTransform(gmath::translate(3.0f, 0.0f, 0.0f));
	//draw
	cubeRenderer.drawMultiple(cubes,shader);
	floor.draw(shader);

	
}

void Sandbox::updateTimer()
{
	deltaTime = timer.getTimeElapsed();
	timeElapsed += timer.getTimeElapsed();
	timer.reset();
}

void Sandbox::initializeShader()
{
	shader.getSourceCode(Shader::Type::Fragment, "shaders/basicFragmentShader.shader");
	shader.getSourceCode(Shader::Type::Vertex, "shaders/basicVertexShader.shader");
	shader.linkProgram();
	shader.bind();
}

