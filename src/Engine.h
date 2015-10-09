#pragma once

#include <vector>
#include "Entity.h"


class Engine
{
public:
	void update() {}
	
private:
	EntityManager entity_manager;
	EventManager event_manager;

};