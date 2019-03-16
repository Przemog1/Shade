#pragma once
#include "Window.h"
#include <GMath/Vector/Vec3f.h>
#include <GMath/Matrix/Mat4f.h>

class Camera
{
public:
	Camera(const gmath::Vec3f& from, const gmath::Vec3f& to, const gmath::Vec3f& up = gmath::Vec3f(0.0f, 1.0f, 0.0f));
	void update(const Window& window, float deltaTime);

	inline const gmath::Mat4f& getViewMatrix() const { return viewMatrix; };

private:
	gmath::Vec2f lastCursorPos;
	float movementSpeed;
	float cameraSensitivity;

	float yaw;
	float pitch;

	gmath::Mat4f viewMatrix;
	gmath::Vec3f from;
	gmath::Vec3f to;
};
