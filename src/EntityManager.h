#pragma once

#include <vector>
#include "Entity.h"


//This needs to generate events for all entities, 
// Then use EventManager to add and delete stuff
class Game;

class EntityManager
{
public:
	//Forward declaration seems to require default constructors and destructors
	//Because it has fields I care about, I also need an init
	EntityManager(Game * game);
	void init();
	~EntityManager();
	void update(Game* game);
	std::vector<Entity> entities;
	Game * game{ nullptr };
};