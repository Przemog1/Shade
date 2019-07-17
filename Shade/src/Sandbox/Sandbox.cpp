#include "Sandbox.h"

#include <GMath/Matrix/Transform.h>
#include <GMath/Matrix/MatrixOperations.h>
#include <vector>
#include <GLFW/glfw3.h>

//TODO: refactorize shader, window, CubeForwardRenderer class 
//TODO: in shader class change getSourceCode
//TODO: extend Timer class (timeElapsed and deltaTime needs to be encapsulated)
//TODO: (redesign?) the camera class

//TODO: shader uniform debug - inform, when shader doesn't have uniform of given name

#include "../Cube.h"
#include "../ShaderManager.h"

#include "../LightSetup.h"
#include "../PointLight.h"


Sandbox::Sandbox(int windowWidth, int windowHeight, const std::string& title)
	:Application(windowWidth,windowHeight,title),
	camera(gmath::Vec3f(0.0f,0.0,0.0), gmath::Vec3f(0.0,2.0f,-1.0f)),
	deltaTime(0.0f),
	timeElapsed(0),
	pointLightSSBO(0),
	mainShader(nullptr)
{
	
}

Sandbox::~Sandbox()
{

}

void Sandbox::onStart()
{
	window.setClearColor(0, 0, 0);
	window.enableDepthTest();

	initializeShaders();
	
	TextureManager::get().addTexture("res/textures/pepe.png", "pepe");
	TextureManager::get().addTexture("res/textures/diffuse.png", "pepeSpecular");

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
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);
	cubes.emplace_back(bezi, beziSpecular);

	for(unsigned int i = 0; i < 60; i++)
		cubes.emplace_back(bezi, beziSpecular);

	for(unsigned int i = 2; i < cubes.size(); i++)
		cubes[i].setTransform(gmath::translate(/*(float)(-i) - 1.5f*/-3.0f -5.0f, 0.0f,(float)i - 50.0f));

	floor.setDiffuseTexture(TextureManager::get().getTexture("woodenFloor"));
	floor.setSpecularTexture(TextureManager::get().getTexture("woodenFloorSpecular"));

		//uniforms
	mainShader = ShaderManager::get().getShader("BlinnPhongShader");
	mainShader->bind();

	perspectiveMatrix = gmath::perspective(90.0f, 16.0f / 9.0f, 0.01f, 100.0f);
	mainShader->uniformMatrix4f("perspectiveMatrix", perspectiveMatrix.getMatrixPtr());

	setLighting();

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
	mainShader->uniformMatrix4f("cameraMatrix", viewMatrix.getMatrixPtr());

	//cube update
	//gmath::Mat4f modelMatrix = gmath::translate(0.0f, 0.0f, -3.0f) * gmath::rotateY(timeElapsed * 3.1415926535f / 4.0f);

	gmath::Mat4f modelMatrix = gmath::translate(0.0f, 0.0f, 0.0f) *gmath::rotateY(timeElapsed * 3.1415926535f / 4.0f) * gmath::scale(0.01f);

	cubes[0].setTransform(modelMatrix);
	cubes[1].setTransform(gmath::translate(3.0f, 0.0f, 0.0f));

	//draw
	cubeRenderer.drawMultiple(cubes,*mainShader);
	floor.draw(*mainShader);
}

void Sandbox::updateTimer()
{
	deltaTime = timer.getTimeElapsed();
	timeElapsed += timer.getTimeElapsed();
	timer.reset();
}

void Sandbox::initializeShaders()
{
	Shader shader;
	shader.getSourceCode(Shader::Type::Vertex, "shaders/BlinnPhongVS.vert");
	shader.getSourceCode(Shader::Type::Fragment, "shaders/BlinnPhongFS.frag");
	shader.linkProgram();

	ShaderManager::get().addShader("BlinnPhongShader", std::move(shader));
}

void Sandbox::setLighting()
{
	LightSetup ls;
	PointLight bulb;

	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			bulb.ambientColor = gmath::Vec3f(0.1f);
			bulb.diffuseColor = (i % 2) == 0 ? gmath::Vec3f(0.1765f, 0.7294f, 0.8275f) : gmath::Vec3f(0.8f, 0.4118f, 0.2588f);
			bulb.specularColor = gmath::Vec3f(0.0f);

			bulb.pos = gmath::Vec3f(j * 3.0f, 0.0f, i * 3.0f);

			ls.addPointLight(bulb);
		}
	}
	
	ls.updateSSBOLightingData(pointLightSSBO);

}

