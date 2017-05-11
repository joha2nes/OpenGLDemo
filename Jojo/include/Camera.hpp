#pragma once

#include "GL\glew.h"
#include "glm\glm.hpp"

struct Plane
{
	Plane(glm::vec3 p, glm::vec3 n);

	glm::vec3 point;
	glm::vec3 normal;
};

struct Frustum
{
	Frustum(Plane n, Plane f, Plane t, Plane b, Plane l, Plane r);

	Plane nearPlane;
	Plane farPlane;
	Plane topPlane;
	Plane bottomPlane;
	Plane leftPlane;
	Plane rightPlane;
};

struct Camera
{
	Camera();
	Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar);

	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 up;
	GLfloat fieldOfView;
	GLfloat aspectRatio;
	GLfloat nearPlaneDistance;
	GLfloat farPlaneDistance;

	glm::mat4 view() const;
	glm::mat4 perspective() const;
	glm::mat4 perspectiveView() const;
	glm::vec3 right() const;
	Frustum frustum() const;
};