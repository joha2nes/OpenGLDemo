#pragma once
#include "Scene.hpp"

class SailingBoat;
struct GUIButtonEvent;
class SceneOne : public Scene
{
public:
	SceneOne(SceneManager*, ResourceManager*);

	void update(float dt) override;
	void input(Input) override;

private:
	void onDemo2Button(GUIButtonEvent);
	void onResumeButton(GUIButtonEvent);
	void onQuitButton(GUIButtonEvent);

	std::vector<SceneObject*> createBoats(ResourceManager*);

	bool m_lookAround;
	glm::vec2 m_cameraRotation;
	bool m_moveForward;
	bool m_moveBackward;
	bool m_strafeLeft;
	bool m_strafeRight;
	bool m_boostSpeed;
	bool m_showMenu;
};