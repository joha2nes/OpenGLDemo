#include "SceneTwo.hpp"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "GUIButton.hpp"
#include "GUIImage.hpp"
#include "GUIText.hpp"
#include "SceneOne.hpp"

SceneTwo::SceneTwo(SceneManager* sm, ResourceManager* rm)
	: Scene(
		sm,
		rm,
		{ 
			rm->loadSceneObject(rm->loadTerrainMesh("assets/heightmap2.png", glm::vec3(10.0f, 100.0f, 10.0f), 3.0f), rm->loadTexture("assets/sea.jpg"), 0.0f, -100.0f, 0.0f)
		},
		{
			rm->loadGUIImage(Rect(0, 0, 1600, 900), rm->loadSprite(rm->loadTexture("assets/cockpit.png"))),
			rm->loadGUIText(Rect(10, 10, 50, 300), rm->loadFont("assets/fonts/arial.ttf"), "DEMO SCENE 2", 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			rm->loadGUIImage(Rect(600, 100, 400, 700), rm->loadSprite(rm->loadTexture("assets/panel.png"))),
			rm->loadGUIText(Rect(655, 175, 400, 50), rm->loadFont("assets/fonts/courbi.ttf"), "PAUSE", 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.9f)),
			rm->loadGUIButton(this, &SceneTwo::onResumeButton, Rect(675, 300, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default_red.png")), rm->loadSprite(rm->loadTexture("assets/button_hover_red.png")), rm->loadSprite(rm->loadTexture("assets/button_press_red.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "RESUME", glm::vec2(36.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
			rm->loadGUIButton(this, &SceneTwo::onDemo2Button, Rect(675, 450, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default_red.png")), rm->loadSprite(rm->loadTexture("assets/button_hover_red.png")), rm->loadSprite(rm->loadTexture("assets/button_press_red.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "DEMO 1", glm::vec2(36.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
			rm->loadGUIButton(this, &SceneTwo::onQuitButton, Rect(675, 600, 250, 100), rm->loadSprite(rm->loadTexture("assets/button_default_red.png")), rm->loadSprite(rm->loadTexture("assets/button_hover_red.png")), rm->loadSprite(rm->loadTexture("assets/button_press_red.png")), Text(rm->loadFont("assets/fonts/courbi.ttf"), "QUIT", glm::vec2(65.0f, 35.0f), 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f))),
		},
		rm->loadSkybox("assets/stars.png"),
		Camera(),
		glm::vec3(1.0f),
		Light(glm::vec3(-1.0f, -0.5f, 1.0f), glm::vec3(0.85f, 0.9f, 1.0f), glm::vec3(0.2f))
	)
{
	m_camera.fieldOfView = 75.0f;
	m_camera.farPlaneDistance = 10000.0f;
	m_camera.position = glm::vec3(0.0f, -10.0f, 100.0f);
	m_showMenu = true;
}
SceneTwo::~SceneTwo()
{}

void SceneTwo::update(float dt)
{
	if (m_showMenu)
		for (auto a : m_guiElements)
			a->setIsActive(true);
	else
	{
		for (auto a : m_guiElements)
			if (a != m_guiElements.at(0))
				a->setIsActive(false);

		m_camera.position += m_camera.viewDirection * dt * 120.0f;

		m_camera.up =
			m_roll == Roll_Left ? glm::mat3(glm::rotate(-glm::radians(dt * 65.0f), m_camera.viewDirection)) * m_camera.up :
			m_roll == Roll_Right ? glm::mat3(glm::rotate(+glm::radians(dt * 65.0f), m_camera.viewDirection)) * m_camera.up :
			m_camera.up;

		m_camera.up =
			m_pitch == Pitch_Up ? glm::mat3(glm::rotate(-glm::radians(dt * 55.0f), m_camera.right())) * m_camera.up :
			m_pitch == Pitch_Down ? glm::mat3(glm::rotate(glm::radians(dt * 55.0f), m_camera.right())) * m_camera.up :
			m_camera.up;
		m_camera.viewDirection =
			m_pitch == Pitch_Up ? glm::mat3(glm::rotate(-glm::radians(dt * 55.0f), m_camera.right())) * m_camera.viewDirection :
			m_pitch == Pitch_Down ? glm::mat3(glm::rotate(glm::radians(dt * 55.0f), m_camera.right())) * m_camera.viewDirection :
			m_camera.viewDirection;

		m_light.direction = glm::mat3(glm::rotate(glm::radians(dt * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f))) * m_light.direction;
	}
}
void SceneTwo::input(Input i)
{
	if (i.type == InputType_Keyboard)
	{
		if (i.keyboard.key == Key_Left || i.keyboard.key == Key_A)
			m_roll = i.keyboard.keyState == KeyState_Pressed ? Roll_Left : Roll_None;
		else if (i.keyboard.key == Key_Right || i.keyboard.key == Key_D)
			m_roll = i.keyboard.keyState == KeyState_Pressed ? Roll_Right : Roll_None;
		else if (i.keyboard.key == Key_Up || i.keyboard.key == Key_W)
			m_pitch = i.keyboard.keyState == KeyState_Pressed ? Pitch_Down : Pitch_None;
		else if (i.keyboard.key == Key_Down || i.keyboard.key == Key_S)
			m_pitch = i.keyboard.keyState == KeyState_Pressed ? Pitch_Up : Pitch_None;
		else if (i.keyboard.key == Key_Escape && i.keyboard.keyState == KeyState_Pressed)
			m_showMenu = !m_showMenu;
	}
}

void SceneTwo::onDemo2Button(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_sceneManager->changeScene(new SceneOne(m_sceneManager, m_resourceManager));
}
void SceneTwo::onResumeButton(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_showMenu = false;
}
void SceneTwo::onQuitButton(GUIButtonEvent e)
{
	if (e.type == GUIButtonEventType_Release)
		m_sceneManager->quit();
}