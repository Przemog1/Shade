#include "Sandbox.h"

#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>

//TODO: refactorize shader, window, CubeForwardRenderer class 
//TODO: extend Timer class (timeElapsed and deltaTime needs to be encapsulated)
//TODO: (redesign?) the camera class

//TODO: shader uniform debug - inform, when shader doesn't have uniform of certain name

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
	window.setClearColor(0, 0, 0);
	window.enableDepthTest();

	TextureManager::get().addTexture("res/textures/pepe.png", "pepe");
	TextureManager::get().addTexture("res/textures/metal_specular.png", "pepeSpecular");

	TextureManager::get().addTexture("res/textures/wooden_floor/wooden_floor_diffuse.png", "woodenFloor");
	TextureManager::get().addTexture("res/textures/wooden_floor/wooden_floor_specular.png", "woodenFloorSpecular");

	TextureManager::get().addTexture("res/textures/bezi.png", "bezi");
	TextureManager::get().addTexture("res/textures/bezi_specular2.png", "beziSpecular");

	const PNGTexture* bezi = TextureManager::get().getTexture("bezi");
	const PNGTexture* beziSpecular = TextureManager::get().getTexture("beziSpecular");
	const PNGTexture* pepe = TextureManager::get().getTexture("pepe");
	const PNGTexture* pepeSpecular = TextureManager::get().getTexture("pepeSpecular");

	cubes.reserve(15);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(pepe, pepeSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);

	for(int i = 2; i < cubes.size(); i++)
		cubes[i].setTransform(gmath::translate((float)(-i) - 1.5f ,0.0f,(float)i - 5.0f));


	floor.setDiffuseTexture(TextureManager::get().getTexture("woodenFloor"));
	floor.setSpecularTexture(TextureManager::get().getTexture("woodenFloorSpecular"));
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
	shader.uniform3f("worldSpaceCameraPos", 2.0f*std::sin(timeElapsed), 0.0f, 2.0f*std::cos(timeElapsed));


	//cube update
	gmath::Mat4f modelMatrix = gmath::translate(0.0f, 0.0f, -3.0f) * gmath::rotateY(timeElapsed * 3.1415926535f / 4.0f);
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
	shader.getSourceCode(Shader::Type::Vertex, "shaders/BlinnPhongVS.shader");
	shader.getSourceCode(Shader::Type::Fragment, "shaders/BlinnPhongFS.shader");
	shader.linkProgram();
	shader.bind();
}

