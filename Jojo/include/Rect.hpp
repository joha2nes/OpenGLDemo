#pragma once
#include "glm\glm.hpp"

struct Rect
{
	int x, y, w, h;

	Rect(int x, int y, int w, int h);
	Rect(glm::ivec2 position, glm::ivec2 size);
	~Rect();

	bool overlaps(glm::ivec2) const;
};