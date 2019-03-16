#include "Application.h"
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


Application::Application(int windowWidth, int windowHeight, const std::string& title)
	:window(windowWidth, windowHeight, title),
	isRunning(true)
{

}

Application::~Application()
{

}

void Application::run()
{
	this->onStart();
	while (!window.shouldClose())
	{
		window.clear();

		this->update();

		window.swapBuffers();
		window.pollEvents();
	}
}