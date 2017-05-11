#pragma once
#include "glm\glm.hpp"
#include <string>

class Font;
struct Text
{
	Font* font;
	std::string text;
	glm::vec2 position;
	float scale;
	glm::vec4 color;

	Text(Font* font, std::string text, glm::vec2 position, float scale, glm::vec4 color);
};