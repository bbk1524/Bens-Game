#include "EntityManager.h"
#include "Game.h"

#include "Logger.h"
extern Logger logger;

void EntityManager::update(Game* game)
{
	for (auto& e : entities)
	{
		e.update();
	}
	logger.log(game->is_valid());
}

EntityManager::EntityManager()
{
	//TODO: rm
	entities.push_back(Entity("TestComponent"));
}

EntityManager::~EntityManager()
{
}
