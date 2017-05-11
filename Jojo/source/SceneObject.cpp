#include "SceneObject.hpp"
#include "Input.hpp"

Transform::Transform(glm::vec3 p)
	: position(p)
	, rotation(glm::vec3(0.0f))
	, scale(glm::vec3(1.0f))
{}
Transform::Transform(glm::vec3 p, glm::vec3 r)
	: position(p)
	, rotation(r)
	, scale(glm::vec3(1.0f))
{}
Transform::Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
	: position(p)
	, rotation(r)
	, scale(s)
{}

SceneObject::SceneObject(Mesh* m, float x, float y, float z)
	: m_mesh(m)
	, m_texture(nullptr)
	, m_transform(Transform(glm::vec3(x, y, z)))
	, m_children({})
{}
SceneObject::SceneObject(Mesh* m, Texture* t, float x, float y, float z)
	: m_mesh(m)
	, m_texture(t)
	, m_transform(Transform(glm::vec3(x, y, z)))
	, m_children({})
{}
SceneObject::SceneObject(Mesh* m, const Transform& tr)
	: m_mesh(m)
	, m_texture(nullptr)
	, m_transform(tr)
	, m_children({})
{}
SceneObject::SceneObject(Mesh* m, Texture* t, const Transform& tr)
	: m_mesh(m)
	, m_texture(t)
	, m_transform(tr)
	, m_children({})
{}
SceneObject::SceneObject(Mesh* m, const Transform& tr, std::vector<SceneObject*> objs)
	: m_mesh(m)
	, m_texture(nullptr)
	, m_transform(tr)
	, m_children(objs)
{}
SceneObject::SceneObject(Mesh* m, float x, float y, float z, std::vector<SceneObject*> objs)
	: m_mesh(m)
	, m_texture(0)
	, m_transform(Transform(glm::vec3(x, y, z)))
	, m_children(objs)
{}
SceneObject::SceneObject(Mesh* m, Texture* t, const Transform& tr, std::vector<SceneObject*> objs)
	: m_mesh(m)
	, m_texture(t)
	, m_transform(tr)
	, m_children(objs)
{}
SceneObject::SceneObject(Mesh* m, Texture* t, float x, float y, float z, std::vector<SceneObject*> objs)
	: m_mesh(m)
	, m_texture(t)
	, m_transform(Transform(glm::vec3(x, y, z)))
	, m_children(objs)
{}
SceneObject::~SceneObject()
{}

void SceneObject::update(float)
{}
void SceneObject::input(Input)
{}

Mesh* SceneObject::getMesh() const 
{
	return m_mesh;
}
Texture* SceneObject::getTexture() const
{
	return m_texture;
}
Transform SceneObject::getTransform() const 
{
	return m_transform;
}
std::vector<SceneObject*> SceneObject::getChildren() const
{
	return m_children;
}
