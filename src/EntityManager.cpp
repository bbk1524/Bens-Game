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
	//entities.push_back(Entity("TestComponent")));
}