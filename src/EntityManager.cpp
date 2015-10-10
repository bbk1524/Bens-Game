#include "EntityManager.h"
//#include "Game.h"
void EntityManager::update()
{
	for (auto& e : entities)
	{
		e.update();
	}
}

EntityManager::EntityManager()
{
	//TODO: rm
	entities.push_back(Entity("TestComponent"));
}