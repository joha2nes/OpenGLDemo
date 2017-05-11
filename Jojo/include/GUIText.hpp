#pragma once
#include "GUIElement.hpp"
#include "Text.hpp"
#include "Rect.hpp"

class GUIText : public GUIElement
{
public:
	GUIText(const Rect&, Font*, std::string, float scale, glm::vec4 color);
	~GUIText();
};