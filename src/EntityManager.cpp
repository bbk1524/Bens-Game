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
}

EntityManager::EntityManager(Game * game)
	: game(game)
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::init()
{
	entities.push_back(Entity("TestComponent", game));
}