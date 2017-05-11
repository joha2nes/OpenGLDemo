#pragma once
#include "Scene.hpp"

class SceneTwo : public Scene
{
public:
	SceneTwo(SceneManager*, ResourceManager*);
	~SceneTwo();

	void update(float dt) override;
	void input(Input) override;

private:
	void onDemo2Button(GUIButtonEvent);
	void onResumeButton(GUIButtonEvent);
	void onQuitButton(GUIButtonEvent);

	enum Pitch
	{
		Pitch_None,
		Pitch_Up,
		Pitch_Down,
	};
	enum Roll
	{
		Roll_None,
		Roll_Left,
		Roll_Right
	};

	Pitch m_pitch;
	Roll m_roll;
	bool m_showMenu;
};