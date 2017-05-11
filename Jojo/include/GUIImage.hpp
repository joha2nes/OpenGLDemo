#pragma once
#include "GUIElement.hpp"

class GUIImage : public GUIElement
{
public:
	GUIImage(Rect, Sprite*);
	~GUIImage();
};