#pragma once
#include <string>
#include <GMath/Vector/Vec2f.h>

struct GLFWwindow;

struct RGBColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

constexpr inline float byteToFloatColorValue(uint8_t colorValue)
{
	return (float)colorValue / 255.0f;
}

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	Window(const Window&) = default;
	Window& operator=(const Window&) = delete;

	bool isKeyPressed(int keyCode) const;
	gmath::Vec2f getCursorPos() const;

	void enableDepthTest();
	void disableDepthTest();

	void setVSyncOn();
	void setVSyncOff();
	void close();
	bool shouldClose();
	void swapBuffers();
	void pollEvents();
	void setClearColor(uint8_t r, uint8_t g, uint8_t b);
	void clear();

private:
	GLFWwindow* window;
	RGBColor clearColor;
	int width;
	int height;
	
private: //on create functions
	void createWindow(const std::string& title);
	void initializeGLFW();
	void initializeGLAD();
	void initializeDebugContext();

	int enabledBuffersFlags;
};
