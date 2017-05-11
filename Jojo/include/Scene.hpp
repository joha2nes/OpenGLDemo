#pragma once
#include "Camera.hpp"
#include "Input.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "SceneObject.hpp"
#include "GUIElement.hpp"
#include "Skybox.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include <vector>

/* TEMPLATE SCENE (header)

#pragma once
#include "Scene.hpp"

class NewScene : public Scene
{
public:
	NewScene(SceneManager*, ResourceManager*);
	~NewScene();

	void update(float dt) override;
	void input(Input) override;
};

*/

struct Light
{
	glm::vec3 direction;
	glm::vec3 diffusion;
	glm::vec3 ambience;
	Light(glm::vec3 direction, glm::vec3 diffusion, glm::vec3 ambience);
};

class Scene
{
public:
	Scene(SceneManager*, ResourceManager*, std::vector<SceneObject*>, std::vector<GUIElement*>, Skybox*, Camera, glm::vec3 backgroundColor, Light light);
	virtual ~Scene();

	virtual void update(float dt);
	virtual void input(Input);

	SceneManager* getSceneManager() const;
	ResourceManager* getResourceManager() const;
	std::vector<SceneObject*> getSceneObjects() const;
	std::vector<GUIElement*> getGUIElements() const;
	Skybox* getSkybox() const;
	Camera getCamera() const;
	glm::vec3 getBackgroundColor() const;
	Light getLight() const;

protected:
	SceneManager* m_sceneManager;
	ResourceManager* m_resourceManager;

	std::vector<SceneObject*> m_sceneOjects;
	std::vector<GUIElement*> m_guiElements;
	Skybox* m_skybox;

	Camera m_camera;
	glm::vec3 m_backgroundColor;
	Light m_light;
};
