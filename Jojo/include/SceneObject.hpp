#pragma once
#include "glm\glm.hpp"
#include <vector>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3);
	Transform(glm::vec3, glm::vec3);
	Transform(glm::vec3, glm::vec3, glm::vec3);
};

struct Input;
class Mesh;
class Texture;
class SceneObject
{
	friend class Scene;
	friend class SceneManager;

public:
	SceneObject(Mesh*, float x, float y, float z);
	SceneObject(Mesh*, Texture*, float x, float y, float z);
	SceneObject(Mesh*, const Transform&);
	SceneObject(Mesh*, Texture*, const Transform&);
	SceneObject(Mesh*, const Transform&, std::vector<SceneObject*>);
	SceneObject(Mesh*, float x, float y, float z, std::vector<SceneObject*>);
	SceneObject(Mesh*, Texture*, const Transform&, std::vector<SceneObject*>);
	SceneObject(Mesh*, Texture*, float x, float y, float z, std::vector<SceneObject*>);
	virtual ~SceneObject();

	virtual void update(float dt);
	virtual void input(Input);

	Mesh* getMesh() const;
	Texture* getTexture() const;
	Transform getTransform() const;
	std::vector<SceneObject*> getChildren() const;

protected:
	Mesh* m_mesh;
	Texture* m_texture;
	Transform m_transform;
	std::vector<SceneObject*> m_children;
};