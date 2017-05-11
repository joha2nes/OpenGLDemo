#include "Camera.hpp"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtx\vector_angle.hpp"

Plane::Plane(glm::vec3 p, glm::vec3 n)
	: point(p)
	, normal(n)
{}

Frustum::Frustum(Plane n, Plane f, Plane t, Plane b, Plane l, Plane r)
	: nearPlane(n)
	, farPlane(f)
	, topPlane(t)
	, bottomPlane(b)
	, leftPlane(l)
	, rightPlane(r)
{}

Camera::Camera()
	: Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 2.0f, 0.1f, 1000.0f)
{}
Camera::Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar)
	: position(position)
	, viewDirection(viewDirection)
	, up(up)
	, fieldOfView(fov)
	, aspectRatio(aspect)
	, nearPlaneDistance(zNear)
	, farPlaneDistance(zFar)
{}
glm::mat4 Camera::view() const
{
	return glm::lookAt(position, position + viewDirection, up);
}
glm::mat4 Camera::perspective() const
{
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlaneDistance, farPlaneDistance);
}
glm::mat4 Camera::perspectiveView() const
{
	return perspective() * view();
}
glm::vec3 Camera::right() const
{
	return normalize(glm::cross(up, viewDirection));
}
Frustum Camera::frustum() const
{
	using namespace glm;

	vec3 r = right();
	vec3 u = normalize(cross(viewDirection, r));

	float fh = 2.0f * tan(radians(fieldOfView / 2.0f)) * farPlaneDistance;
	float fw = fh * aspectRatio;

	vec3 fc = position + viewDirection * farPlaneDistance;
	vec3 ftc = fc + (u * (fh / 2.0f));
	vec3 fbc = fc - (u * (fh / 2.0f));
	vec3 flc = fc - (r * (fw / 2.0f));
	vec3 frc = fc + (r * (fw / 2.0f));

	return Frustum(
		Plane(position + nearPlaneDistance * viewDirection, viewDirection),
		Plane(position + farPlaneDistance * viewDirection, -viewDirection),
		Plane(position, normalize(cross(r, ftc - position))),
		Plane(position, -normalize(cross(r, fbc - position))),
		Plane(position, -normalize(cross(flc - position, u))),
		Plane(position, normalize(cross(frc - position, u)))
		);
}