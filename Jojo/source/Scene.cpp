#include "Scene.hpp"

Light::Light(glm::vec3 direction, glm::vec3 diffusion, glm::vec3 ambience)
	: direction(direction)
	, diffusion(diffusion)
	, ambience(ambience)
{}

Scene::Scene(SceneManager* sm, ResourceManager* rm, std::vector<SceneObject*> objs, std::vector<GUIElement*> guis, Skybox* sb, Camera cam, glm::vec3 bg, Light l)
	: m_sceneManager(sm)
	, m_resourceManager(rm)
	, m_sceneOjects(objs)
	, m_guiElements(guis)
	, m_skybox(sb)
	, m_camera(cam)
	, m_backgroundColor(bg)
	, m_light(glm::normalize(l.direction), l.diffusion, l.ambience)
{}
Scene::~Scene()
{}

void Scene::update(float)
{}
void Scene::input(Input)
{}

SceneManager* Scene::getSceneManager() const
{
	return m_sceneManager;
}
ResourceManager* Scene::getResourceManager() const
{
	return m_resourceManager;
}
std::vector<SceneObject*> Scene::getSceneObjects() const
{
	return m_sceneOjects;
}
std::vector<GUIElement*> Scene::getGUIElements() const
{
	return m_guiElements;
}
Skybox* Scene::getSkybox() const
{
	return m_skybox;
}
Camera Scene::getCamera() const
{
	return m_camera;
}
glm::vec3 Scene::getBackgroundColor() const
{
	return m_backgroundColor;
}
Light Scene::getLight() const
{
	return m_light;
}
