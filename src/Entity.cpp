#include "Entity.h"
#include "Component.h"

#include "TestComponent.h"
#include "CompPosition.h"

#include <memory>

#include "Logger.h"
extern Logger logger;

#include "Game.h"

//How the heck am I supposed to pass stuff to the
//init functions?
//In my final, I passed in a Game* and an x,y,angle
//Here, I want to just add components from the call, not the constructor
//Ex:
/*
if (entity_manager.detects_collision_at(x,y)
{
    auto exp = std::make_unique<Entity>("explosion");
    exp.add_component<Position>(x,y,0);
    exp.add_component<Timer>(5);
    etc...
}
*/

//I want to use the standard system of each component having only data, and making "Systems" which read and write to the components on update
Entity::Entity(std::string type, Game * game)
    : type(type),
    game(game)
{
    if (type == "TestComponent")
    {
        add_component<TestComponent>();
    }
    else if (type == "CompPosition")
    {
        add_component<CompPosition>(0.f, 0.f, 0.f);
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

// Entity::~Entity()
// {

// }
void Entity::update()
{
    for (auto& c : components)
    {
        c->update();
    }
}
