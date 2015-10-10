#pragma once

#include <vector>
#include "Entity.h"


//This needs to generate events for all entities, 
// Then use EventManager to add and delete stuff

class EntityManager
{
public:
	void update();
	EntityManager();
	std::vector<Entity> entities;
};