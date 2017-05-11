#include "Text.hpp"

Text::Text(Font* font, std::string text, glm::vec2 position, float scale, glm::vec4 color)
	: font(font)
	, text(text)
	, position(position)
	, scale(scale)
	, color(color)
{}
