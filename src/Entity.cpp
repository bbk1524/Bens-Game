#include "Entity.h"
#include "Component.h"

#include "TestComponent.h"

#include <memory>

#include "Logger.h"
extern Logger logger;

#include "Game.h"

//How the heck am I supposed to pass stuff to the
//init functions?
//In my final, I passed in a Game* and an x,y,angle

//I want to use the standard system of each component having only data, and making "Systems" which read and write to the components on update
Entity::Entity(std::string type, Game * game)
	: type(type),
	game(game)
{
	if (type == "TestComponent")
	{
		add_component<TestComponent>();
	}
	else
	{
		logger.log(type, "not found");
	}
}

Entity::Entity(Entity && other)
	: type(other.type),
	game(other.game)
{
	components.insert(components.end(),
		std::make_move_iterator(other.components.begin()),
		std::make_move_iterator(other.components.end()));
}

void Entity::update()
{
	for (auto& c : components)
	{
		c->update();
	}
}
