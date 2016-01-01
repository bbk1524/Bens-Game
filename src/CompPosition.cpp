#include "Definitions.h"
#include "CompPosition.h"
#include "Logger.h"
#include "Entity.h"
#include "Game.h"
#include "InputSystem.h"

extern Logger logger;

CompPosition::CompPosition(Entity * owner)
    : Component(owner)
{}

void CompPosition::update()
{
    if( get_owner()->game->input_system.get_event(game_event::UP ))
    {
        y -= 1;
    }
    if( get_owner()->game->input_system.get_event(game_event::DOWN))
    {
        y += 1;
    }
    if( get_owner()->game->input_system.get_event(game_event::LEFT))
    {
        x -= 1;
    }
    if( get_owner()->game->input_system.get_event(game_event::RIGHT))
    {
        x += 1;
    }

    //check bounds in here for now, but I will want to change this..
    if( x > 10) { x = 10; }
    if( y > 10) { y = 10; }
    if( x < -10) { x = -10; }
    if( y < -10) { y = -10; }
    logger.log("position: ", x, y);
}

void CompPosition::init(float x, float y, float angle)
{
    this->x = x;
    this->y = y;
    this->angle = angle;
}
