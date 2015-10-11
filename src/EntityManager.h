#pragma once

#include <vector>
#include "Entity.h"


//This needs to generate events for all entities, 
// Then use EventManager to add and delete stuff
class Game;

class EntityManager
{
public:
	//Forward declaration seems to require constructors and destructors
	EntityManager();
	~EntityManager();
	void update(Game* game);
	std::vector<Entity> entities;
};