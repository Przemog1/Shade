#include "Camera.h"
#include "Window.h"
#include <GMath/Vector/VectorOperations.h>
#include <GMath/Matrix/Transform.h>
#include <GMath/Util.h>
#include <GLFW/glfw3.h>

void Camera::update(const Window& window, float deltaTime)
{
	gmath::Vec2f cursorPos = window.getCursorPos();

	pitch += (cursorPos.y - lastCursorPos.y) * cameraSensitivity;
	yaw += (cursorPos.x - lastCursorPos.x) * cameraSensitivity;

	 pitch = 0.0f;

	lastCursorPos.x = cursorPos.x;
	lastCursorPos.y = cursorPos.y;

	if (pitch >= 90.0f)
		pitch = 89.0f;
	if (pitch <= -90.0f)
		pitch = -89.0f;


	to.x = cos(gmath::degToRad(yaw)) * cos(gmath::degToRad(pitch)) + from.x;
	to.y = -sin(gmath::degToRad(pitch)) + from.y;
	to.z = sin(gmath::degToRad(yaw)) * cos(gmath::degToRad(pitch)) + from.z;

	gmath::Vec3f tmp;
	const gmath::Vec3f up = { 0.0f,1.0f,0.0f };
	float dt = deltaTime * movementSpeed;

	if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		movementSpeed = 20.0f;
	else
		movementSpeed = 5.0f;

	if (window.isKeyPressed(GLFW_KEY_A))
	{
		tmp = gmath::crossProduct((from - to),up);//tmp = (from - to).crossProduct(up);
		tmp.normalize();

		tmp.x *= dt;
		tmp.y = 0.0f;
		tmp.z *= dt;

		from = from + tmp;
		to = to + tmp;
	}
	else
	if (window.isKeyPressed(GLFW_KEY_D))
	{
		tmp = gmath::crossProduct((to - from), up);
		tmp.normalize();

		tmp.x *= dt;
		tmp.y = 0.0f;
		tmp.z *= dt;

		from = from + tmp;
		to = to + tmp;
	}
	else
	if (window.isKeyPressed(GLFW_KEY_W))
	{
		tmp = to - from;
		tmp.normalize();

		tmp.x *= dt;
		tmp.y = 0.0f;
		tmp.z *= dt;



		from = from + tmp;
		to = to + tmp;

	}
	else
	if (window.isKeyPressed(GLFW_KEY_S))
	{
		tmp = from - to;
		tmp.normalize();

		tmp.x *= dt;
		tmp.y = 0.0f;
		tmp.z *= dt;



		from = from + tmp;
		to = to + tmp;
	}

	viewMatrix = gmath::lookAt(from, to);
}

Camera::Camera(const gmath::Vec3f& from, const gmath::Vec3f& to, const gmath::Vec3f& up)
	:lastCursorPos(0.0f),
	movementSpeed(5.0f),
	cameraSensitivity(0.09f),
	yaw(0.0f),
	pitch(0.0f),
	from(from),
	to(to)
{
	viewMatrix = gmath::lookAt(from, to, up);
}