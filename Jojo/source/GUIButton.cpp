#include "GUIButton.hpp"
#include "Sprite.hpp"
#include "Input.hpp"
#include "Text.hpp"

GUIButtonEvent::GUIButtonEvent(GUIButton* b, GUIButtonEventType t)
	: button(b)
	, type(t)
{}

GUIButton::~GUIButton()
{
#define del(a) { if (a != nullptr) delete a; a = nullptr; }
	del(m_listener);
}

void GUIButton::input(Input input)
{
	glm::ivec2 mousePos = glm::ivec2(input.mouseButton.position.x, input.mouseButton.position.y);
	if (input.type == InputType_MouseButton && input.mouseButton.button == MouseButton_Left && overlaps(mousePos))
	{
		if (input.mouseButton.state == MouseButtonState_Down)
		{
			m_isPressed = true;
			m_spriteObjects.at(0) = m_spriteOnPress;
			m_listener->invoke(GUIButtonEvent(this, GUIButtonEventType_Press));
		}
		else if (input.mouseButton.state == MouseButtonState_Up && m_isPressed)
		{
			m_isPressed = false;
			m_spriteObjects.at(0) = m_spriteOnHover;
			m_listener->invoke(GUIButtonEvent(this, GUIButtonEventType_Release));
		}
	}
	else if (input.type == InputType_MouseMovement)
	{
		mousePos = glm::ivec2(input.mouseMovement.position.x, input.mouseMovement.position.y);
		bool isOverlapping = overlaps(mousePos);
		m_spriteObjects.at(0) =
			!isOverlapping ? m_defaultSprite :
			isOverlapping && !m_isPressed ? m_spriteOnHover :
			m_spriteObjects.at(0);

		if (!isOverlapping)
			m_isPressed = false;
	}
}

bool GUIButton::isPressed() const
{
	return m_isPressed;
}
bool GUIButton::overlaps(glm::ivec2 p) const
{
	return
		p.x >= m_rect.x &&
		p.x <= m_rect.x + m_rect.w &&
		p.y >= m_rect.y &&
		p.y <= m_rect.y + m_rect.h;
}