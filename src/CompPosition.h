#pragma once

#include "Component.h"

class CompPosition : public Component
{
public:
	CompPosition(Entity * owner);
	~CompPosition() = default;
	void update() override;
	void init(float x, float y, float angle);
        int dx{1};
        int dy{1};
        float x;
        float y;
        float angle;
};
