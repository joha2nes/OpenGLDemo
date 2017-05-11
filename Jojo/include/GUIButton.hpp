#pragma once
#include "GUIElement.hpp"
#include "functor.hpp"
#include <vector>

enum GUIButtonEventType
{
	GUIButtonEventType_Press,
	GUIButtonEventType_Release,
};

class GUIButton;
struct GUIButtonEvent
{
	GUIButton* button;
	GUIButtonEventType type;

	GUIButtonEvent(GUIButton*, GUIButtonEventType);
};

class GUIButton : public GUIElement
{
public:
	template <typename T>
	GUIButton(T* object, void(T::*method)(GUIButtonEvent event), Rect rect, Sprite* defaultSprite, Sprite* hoverSprite, Sprite* pressSprite, Text text)
		: GUIElement(rect, { text }, { defaultSprite })
		, m_listener(new Functor<T, GUIButtonEvent>(object, method))
		, m_defaultSprite(defaultSprite)
		, m_spriteOnHover(hoverSprite)
		, m_spriteOnPress(pressSprite)
		, m_isPressed(false)
	{}
	~GUIButton();

	void input(Input) override;

	bool isPressed() const;
	bool overlaps(glm::ivec2) const;

private:
	IFunctor<GUIButtonEvent>* m_listener;
	Sprite* m_defaultSprite;
	Sprite* m_spriteOnHover;
	Sprite* m_spriteOnPress;
	bool m_isPressed;
};