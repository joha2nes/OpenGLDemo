#pragma once
#include "glm\glm.hpp"
#include "Text.hpp"
#include "Rect.hpp"
#include <vector>

struct Input;
class Sprite;
class GUIElement
{
public:
	GUIElement(Rect, std::vector<Text>, std::vector<Sprite*>);
	virtual ~GUIElement();

	virtual void input(Input);
	virtual void update(float dt);

	Rect getRect() const;
	std::vector<Text> getTextObjects() const;
	std::vector<Sprite*> getSpriteObjects() const;
	
	void setIsActive(bool);
	bool isActive() const;

protected:
	Rect m_rect;
	std::vector<Text> m_textObjects;
	std::vector<Sprite*> m_spriteObjects;
	bool m_isActive;
};