#include "SceneManager.hpp"
#include "Scene.hpp"
#include "SceneObject.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "GL/glew.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtx/euler_angles.hpp"
#include "SceneOne.hpp"
#include "GUIElement.hpp"
#include "Sprite.hpp"
#include <algorithm>

SceneManager::SceneManager()
{
	m_resourceManager = new ResourceManager();
	m_meshShader = new Shader("assets/shaders/mesh.vs", "assets/shaders/mesh.fs");
	m_spriteShader = new Shader("assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
	m_textShader = new Shader("assets/shaders/text.vs", "assets/shaders/text.fs");
	m_skyboxShader = new Shader("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
	m_activeScene = new SceneOne(this, m_resourceManager);
	m_quitRequested = false;
}
SceneManager::~SceneManager()
{
	delete m_activeScene;
	delete m_resourceManager;
	delete m_meshShader;
	delete m_spriteShader;
	delete m_textShader;
	delete m_skyboxShader;
}

void SceneManager::update(float dt)
{
	m_activeScene->update(dt);
	updateSceneObjects(dt, m_activeScene->getSceneObjects());
	for (auto gui : m_activeScene->getGUIElements()) if (gui->isActive()) gui->update(dt);
}
void SceneManager::draw()
{
	glm::vec3 clearColor = m_activeScene->getBackgroundColor();
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_BLEND);

	// draw skybox
	if (m_activeScene->getSkybox() != nullptr)
	{
		glDisable(GL_DEPTH_TEST);

		m_skyboxShader->bind();
		m_skyboxShader->setMatrix4("projection", m_activeScene->getCamera().perspective());
		m_skyboxShader->setMatrix4("view", m_activeScene->getCamera().view());
		m_skyboxShader->setVector3("cameraPosition", m_activeScene->getCamera().position);
		
		m_activeScene->getSkybox()->draw();
	}

	// draw scene objects
	if (m_activeScene->getSceneObjects().size() > 0)
	{
		glEnable(GL_DEPTH_TEST);

		m_meshShader->bind();
		m_meshShader->setMatrix4("projection", m_activeScene->getCamera().perspective());
		m_meshShader->setMatrix4("view", m_activeScene->getCamera().view());
		m_meshShader->setVector3("light.direction", m_activeScene->getLight().direction);
		m_meshShader->setVector3("light.diffusion", m_activeScene->getLight().diffusion);
		m_meshShader->setVector3("light.ambience", m_activeScene->getLight().ambience);

		drawSceneObjects(glm::mat4(), m_activeScene->getSceneObjects());
	}

	// draw gui elements
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (m_activeScene->getGUIElements().size() > 0)
	{
		glDisable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);

		m_spriteShader->bind();
		m_spriteShader->setMatrix4("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f)); // HARDCODED

		for (auto gui : m_activeScene->getGUIElements())
		{
			if (!gui->isActive())
				continue;
			else {
				m_spriteShader->bind();
				for (auto sprite : gui->getSpriteObjects())
				{
					float x = (float)gui->getRect().x;
					float y = (float)gui->getRect().y;
					float w = (float)gui->getRect().w;
					float h = (float)gui->getRect().h;
					m_spriteShader->setMatrix4("transformation", glm::translate(glm::vec3(x, y, 0.0f)) * glm::scale(glm::vec3(w, h, 0.0f)));

					sprite->draw();
				}
				m_textShader->bind();
				for (auto text : gui->getTextObjects())
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					m_textShader->bind();
					m_textShader->setMatrix4("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f)); // HARDCODED

					drawText(text, glm::vec2(gui->getRect().x, gui->getRect().y));
				}
			}
		}
	}
}
void SceneManager::input(Input input)
{
	m_activeScene->input(input);
	inputSceneObjects(input, m_activeScene->getSceneObjects());
	for (auto gui : m_activeScene->getGUIElements()) if (gui->isActive()) gui->input(input);
}
void SceneManager::changeScene(Scene* newScene)
{
	delete m_activeScene;
	m_activeScene = newScene;
}

bool SceneManager::insideFrustum(const glm::mat4& world, const SceneObject* obj) const
{
	Frustum frustum = m_activeScene->getCamera().frustum();
	glm::vec3 position = glm::vec3(world * glm::vec4(obj->m_transform.position, 1.0f));
	float radius = sceneObjectRadius(obj);
	return
		dot(position - frustum.nearPlane.point, frustum.nearPlane.normal) + radius >= 0.0f &&
		dot(position - frustum.farPlane.point, frustum.farPlane.normal) + radius >= 0.0f &&
		dot(position - frustum.leftPlane.point, frustum.leftPlane.normal) + radius >= 0.0f &&
		dot(position - frustum.rightPlane.point, frustum.rightPlane.normal) + radius >= 0.0f &&
		dot(position - frustum.topPlane.point, frustum.topPlane.normal) + radius >= 0.0f &&
		dot(position - frustum.bottomPlane.point, frustum.bottomPlane.normal) + radius >= 0.0f;
}
void SceneManager::drawSceneObjects(const glm::mat4& world, const std::vector<SceneObject*>& objects) const
{
	for (auto obj : objects)
		if (insideFrustum(world, obj))
		{
			glm::mat4 translation = glm::translate(obj->getTransform().position);
			glm::mat4 rotation = glm::eulerAngleXYZ(
				glm::radians(obj->getTransform().rotation.x), 
				glm::radians(obj->getTransform().rotation.y), 
				glm::radians(obj->getTransform().rotation.z));
			glm::mat4 scaling = glm::scale(obj->getTransform().scale);
			glm::mat4 transformation = world * translation * rotation * scaling;

			m_meshShader->setMatrix4("model", transformation);

			if (obj->getTexture() != nullptr)
				obj->getTexture()->bind();

			if (obj->getMesh() != nullptr)
			{
				obj->getMesh()->bind();
				obj->getMesh()->draw();
			}
			drawSceneObjects(transformation, obj->getChildren());
		}
}
void SceneManager::drawText(const Text& text, glm::vec2 position) const
{
	m_textShader->setVector4("color", text.color);

	glm::vec2 accPos = position + text.position;
	for (char character : text.text)
	{
		Glyph glyph = text.font->getGlyph(character);

		m_textShader->setMatrix4("transformation", glm::translate(glm::vec3(accPos, 0.0f)) * glm::scale(glm::vec3(text.scale)));

		glBindTexture(GL_TEXTURE_2D, glyph.textureObj);
		glBindVertexArray(glyph.vertexArrayObj);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		accPos.x += (float)glyph.advance * text.scale;
	}
}
void SceneManager::updateSceneObjects(float dt, const std::vector<SceneObject*>& objects)
{
	for (auto obj : objects)
	{
		obj->update(dt);
		updateSceneObjects(dt, obj->getChildren());
	}
}
void SceneManager::inputSceneObjects(Input input, const std::vector<SceneObject*>& objects)
{
	for (auto obj : objects)
	{
		obj->input(input);
		inputSceneObjects(input, obj->getChildren());
	}
}
float SceneManager::sceneObjectRadius(const SceneObject* obj) const
{
	float maxScaledAxis = std::max(obj->getTransform().scale.x, std::max(obj->getTransform().scale.y, obj->getTransform().scale.z));
	float parentRadius = glm::length(obj->getTransform().position) + maxScaledAxis * (obj->getMesh() == nullptr ? 0.0f : obj->getMesh()->getRadius());
	float maxChildRadius = 0.0f;
	for (auto child : obj->getChildren())
	{
		float currentChildRadius = sceneObjectRadius(child);
		if (currentChildRadius > maxChildRadius)
			maxChildRadius = currentChildRadius;
	}
	return std::max(parentRadius, maxChildRadius);
}
void SceneManager::quit()
{
	m_quitRequested = true;
}
bool SceneManager::isQuitRequested() const
{
	return m_quitRequested;
}