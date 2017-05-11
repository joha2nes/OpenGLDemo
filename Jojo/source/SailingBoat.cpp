#include "SailingBoat.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtx\euler_angles.hpp"

SailingBoat::SailingBoat(Mesh* m, Texture* t, Transform tr, float startTime, std::vector<SceneObject*> objs)
	: SceneObject(m, t, tr, objs)
	, m_time(startTime)
{}
SailingBoat::~SailingBoat()
{}

void SailingBoat::update(float dt)
{
	m_time += dt;

	m_transform.rotation = glm::mat3(glm::rotate(glm::radians(glm::sin(m_time * 2.0f) * 0.05f), glm::vec3(0.0f, 0.0f, 1.0f))) * m_transform.rotation;
}