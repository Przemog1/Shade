#include "Window.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <exception>

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam);

Window::Window(int width, int height, const std::string& title)
	:width(width),
	height(height),
	clearColor({ 0, 0, 0 }),
	enabledBuffersFlags(0x00000000)
{
	initializeGLFW();
	createWindow(title);
	initializeGLAD();
	setVSyncOn();
	initializeDebugContext();
	

	enabledBuffersFlags = enabledBuffersFlags | GL_COLOR_BUFFER_BIT;

	glEnable(GL_CULL_FACE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::isKeyPressed(int keyCode) const
{
	return (GLFW_PRESS == glfwGetKey(window, keyCode));
}

gmath::Vec2f Window::getCursorPos() const
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	return gmath::Vec2f(static_cast<float>(x), static_cast<float>(y));
}

void Window::close()
{
	glfwSetWindowShouldClose(window,GLFW_TRUE);
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::enableDepthTest()
{
	enabledBuffersFlags;
	enabledBuffersFlags;
	glEnable(GL_DEPTH_TEST);
	enabledBuffersFlags = enabledBuffersFlags | GL_DEPTH_BUFFER_BIT;
	enabledBuffersFlags;
	enabledBuffersFlags;
	
}
void Window::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);

	enabledBuffersFlags = enabledBuffersFlags & (0xFFFFFFFF ^ GL_DEPTH_BUFFER_BIT);
	enabledBuffersFlags;
	enabledBuffersFlags;
}

void Window::setVSyncOn()
{
	glfwSwapInterval(1);
}

void Window::setVSyncOff()
{
	glfwSwapInterval(0);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::setClearColor(uint8_t r, uint8_t g, uint8_t b)
{
	glClearColor(byteToFloatColorValue(r), byteToFloatColorValue(g), byteToFloatColorValue(b), 1.0f);
}

void Window::clear()
{
	glClear(enabledBuffersFlags);
}

void Window::createWindow(const std::string& title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "failed to create window.\n";
		std::cin.get();
		std::terminate();
	}

	glfwMakeContextCurrent(window);
}

void Window::initializeGLFW()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize glfw.\n";
		std::cin.get();
		std::terminate();
	}
}

void Window::initializeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad.\n";
		std::cin.get();
	}
}

void Window::initializeDebugContext()
{
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}