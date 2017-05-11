#include "GUIElement.hpp"
#include "Input.hpp"

GUIElement::GUIElement(Rect r, std::vector<Text> t, std::vector<Sprite*> s)
	: m_rect(r)
	, m_textObjects(t)
	, m_spriteObjects(s)
	, m_isActive(true)
{}
GUIElement::~GUIElement()
{}

void GUIElement::input(Input)
{}
void GUIElement::update(float)
{}

Rect GUIElement::getRect() const
{
	return m_rect;
}
std::vector<Text> GUIElement::getTextObjects() const
{
	return m_textObjects;
}
std::vector<Sprite*> GUIElement::getSpriteObjects() const
{
	return m_spriteObjects;
}
void GUIElement::setIsActive(bool a)
{
	m_isActive = a;
}
bool GUIElement::isActive() const
{
	return m_isActive;
}
