#pragma once
#include <string>
#include <vector>
#include <map>
#include "glm\glm.hpp"

struct Input;
class Shader;
class Scene;
class SceneObject;
class ResourceManager;
struct Text;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void input(Input);
	void update(float dt);
	void draw();

	void changeScene(Scene*);
	void quit();

	bool isQuitRequested() const;

private:
	bool insideFrustum(const glm::mat4& world, const SceneObject*) const;
	void drawSceneObjects(const glm::mat4& world, const std::vector<SceneObject*>& objects) const;
	void drawText(const Text&, glm::vec2) const;
	void updateSceneObjects(float dt, const std::vector<SceneObject*>& objects);
	void inputSceneObjects(Input, const std::vector<SceneObject*>& objects);
	float sceneObjectRadius(const SceneObject*) const;

private:
	Scene* m_activeScene;

	ResourceManager* m_resourceManager;

	Shader* m_meshShader;
	Shader* m_spriteShader;
	Shader* m_textShader;
	Shader* m_skyboxShader;

	std::vector<Text> m_info;

	bool m_quitRequested;
};