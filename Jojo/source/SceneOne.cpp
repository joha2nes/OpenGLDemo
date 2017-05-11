#include "SceneOne.hpp"
#include "glm\gtx\transform.hpp"
#include "GUIButton.hpp"
#include "GUIImage.hpp"
#include "GUIText.hpp"
#include "Rect.hpp"
#include "SceneTwo.hpp"
#include <random>
#include <ctime>

SceneOne::SceneOne(SceneManager* sm, ResourceManager* rm)
	: Scene(
		sm,
		rm,
		{
			rm->loadSceneObject(rm->loadTerrainMesh("assets/seglinge.png", glm::vec3(2.0f, 30.0f, 2.0f), 8.0f), rm->loadTexture("assets/rock.png"), 0.0f, -10.0f, 0.0f),
			rm->loadSceneObject(rm->loadTerrainMesh("assets/seglinge.png", glm::vec3(2.0f, 0.0f, 2.0f), 5.0f), rm->loadTexture("assets/sea.jpg"), Transform(glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
			{
				createBoats(rm),
			}
			),
		},
		{
			rm->loadGUIText(Rect(10, 10, 50, 300), rm->loadFont("assets/fonts/arial.ttf"), "DEMO SCENE 1", 0.8f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			rm->loadGUIImage(Rect(600, 100, 400, 700), rm->loadSprite(rm->loadTexture("assets/panel.png"))),
			rm->loadGUIText(Rect(655, 175, 400, 50), rm->loadFont("assets/fonts/courbi.ttf"), "PAUSE", 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.9f)),
			rm->loadGUIButton(this, &SceneOne::onResumeButton, Rect(675, 300, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default.png")), rm->loadSprite(rm->loadTexture("assets/button_hover.png")), rm->loadSprite(rm->loadTexture("assets/button_press.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "RESUME", glm::vec2(36.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
			rm->loadGUIButton(this, &SceneOne::onDemo2Button, Rect(675, 450, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default.png")), rm->loadSprite(rm->loadTexture("assets/button_hover.png")), rm->loadSprite(rm->loadTexture("assets/button_press.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "DEMO 2", glm::vec2(36.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
			rm->loadGUIButton(this, &SceneOne::onQuitButton, Rect(675, 600, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default.png")), rm->loadSprite(rm->loadTexture("assets/button_hover.png")), rm->loadSprite(rm->loadTexture("assets/button_press.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "QUIT", glm::vec2(65.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
		},
		rm->loadSkybox("assets/skybox.jpg"),
		Camera(),
		glm::vec3(0.1f, 0.2f, 0.3f),
		Light(glm::vec3(-1.0f, -0.2f, 1.0f), glm::vec3(0.8f), glm::vec3(0.6f))
		)
	, m_lookAround(false)
	, m_cameraRotation(glm::vec2(0.0f))
	, m_moveForward(false)
	, m_moveBackward(false)
	, m_boostSpeed(false)
	, m_strafeLeft(false)
	, m_strafeRight(false)
	, m_showMenu(true)
{
	m_camera.position = glm::vec3(-15.1883650f, 2.73367357f, 17.4836464f);
	m_camera.viewDirection = glm::vec3(0.953056455f, 0.0376322195f, -0.300464869f);
}

void SceneOne::update(float dt)
{
	if (!m_showMenu)
	{
		for (auto a : m_guiElements)
			a->setIsActive(false);

		float speed = m_boostSpeed ? 100.0f : 30.0f;
		m_camera.position +=
			m_moveForward ? m_camera.viewDirection * dt * speed :
			m_moveBackward ? -m_camera.viewDirection * dt * speed :
			glm::vec3(0.0f);
		m_camera.position +=
			m_strafeLeft ? m_camera.right() * dt * speed : // left?? -right?? bug
			m_strafeRight ? -m_camera.right() * dt * speed :
			glm::vec3(0.0f);

		m_camera.position.y = m_camera.position.y < -2.5f ? -2.5f : m_camera.position.y;

		float sensitivity = 0.007f;
		if (m_lookAround)
			m_camera.viewDirection =
			glm::mat3(glm::rotate(m_cameraRotation.y * sensitivity, m_camera.right())) *
			glm::mat3(glm::rotate(-m_cameraRotation.x * sensitivity, m_camera.up)) *
			m_camera.viewDirection;

		m_cameraRotation = glm::vec2(0.0f);
	}
	else
		for (auto a : m_guiElements)
			a->setIsActive(true);
}
void SceneOne::input(Input i)
{
	if (i.type == InputType_MouseButton) {
		if (i.mouseButton.button == MouseButton_Right) {
			m_lookAround = i.mouseButton.state == MouseButtonState_Down;
		}
	}
	else if (i.type == InputType_MouseMovement) {
		m_cameraRotation = (glm::vec2)i.mouseMovement.movement;
	}
	else if (i.type == InputType_Keyboard) {
		if (i.keyboard.key == Key_W) {
			m_moveForward = i.keyboard.keyState == KeyState_Pressed;
		}
		else if (i.keyboard.key == Key_S) {
			m_moveBackward = i.keyboard.keyState == KeyState_Pressed;
		}
		else if (i.keyboard.key == Key_A) {
			m_strafeLeft = i.keyboard.keyState == KeyState_Pressed;
		}
		else if (i.keyboard.key == Key_D) {
			m_strafeRight = i.keyboard.keyState == KeyState_Pressed;
		}
		else if (i.keyboard.key == Key_Space)
			m_boostSpeed = i.keyboard.keyState == KeyState_Pressed;
		else if (i.keyboard.key == Key_Escape)
			if (i.keyboard.keyState == KeyState_Pressed)
				m_showMenu = !m_showMenu;
	}
}

void SceneOne::onDemo2Button(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_sceneManager->changeScene(new SceneTwo(m_sceneManager, m_resourceManager));
}
void SceneOne::onResumeButton(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_showMenu = false;
}
void SceneOne::onQuitButton(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_sceneManager->quit();
}

std::vector<SceneObject*> SceneOne::createBoats(ResourceManager* rm)
{
	std::vector<SceneObject*> result;
	srand(clock());
	for (int i = 0; i < 200; i++)
	{
		float xPosition = (float)(rand() % 75) - 50.0f;
		float zPosition = (float)(rand() % 75) - 20.0f;
		float yRotation = (float)(rand() % 360);
		result.push_back(
			rm->loadSailingBoat(nullptr, nullptr, Transform(glm::vec3(xPosition, 0.0f, zPosition), glm::vec3(0.0f, yRotation, 0.0f)), (float)rand(),
			{
				rm->loadSceneObject(rm->loadTriangleMesh(), rm->loadTexture("assets/sail.jpg"), Transform(glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 3.0f, 1.0f))),
				rm->loadSceneObject(rm->loadTriangleMesh(), rm->loadTexture("assets/sail.jpg"), Transform(glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 180.0f, .0f), glm::vec3(1.0f, 3.0f, 1.0f))),
			}
			)
		);
	}
	return result;
}