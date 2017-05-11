#pragma once
#include "SceneObject.hpp"

class SailingBoat : public SceneObject
{
public:
	SailingBoat(Mesh*, Texture*, Transform, float startTime, std::vector<SceneObject*>);
	~SailingBoat();

	void update(float dt) override;

private:
	float m_time;
};