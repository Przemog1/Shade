#pragma once
#include <string>
#include "Window.h"

class Application
{
public:
	Application(int windowWidth, int windowHeight, const std::string& title);
	virtual ~Application();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void run();

	inline Window& getWindow() { return window; };

protected:
	virtual void onStart() = 0;
	virtual void update() = 0;

	bool isRunning;
	Window window;
};