#pragma once

#include "Component.h"

class TestComponent : public Component
{
public:
	TestComponent(Entity * owner);
	~TestComponent() = default;
	void update() override;
	int a{ 5 };
	void init();

};