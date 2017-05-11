#include "Rect.hpp"

Rect::Rect(int x, int y, int w, int h)
	: x(x)
	, y(y)
	, w(w)
	, h(h)
{}
Rect::Rect(glm::ivec2 position, glm::ivec2 size)
	: x(position.x)
	, y(position.y)
	, w(size.x)
	, h(size.x)
{}
Rect::~Rect()
{}

bool Rect::overlaps(glm::ivec2 p) const
{
	return
		p.x >= x &&
		p.x <= x + w &&
		p.x >= y + h &&
		p.x <= y;
}
