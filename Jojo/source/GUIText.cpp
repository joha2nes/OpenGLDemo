#include "GUIText.hpp"

GUIText::GUIText(const Rect& r, Font* f, std::string s, float scale, glm::vec4 c)
	: GUIElement(r, { Text(f, s, glm::vec2(0.0f), scale, c) }, {})
{}
GUIText::~GUIText()
{}