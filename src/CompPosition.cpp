#include "CompPosition.h"
#include "Logger.h"
#include "Entity.h"
#include "Game.h"

extern Logger logger;

CompPosition::CompPosition(Entity * owner)
    : Component(owner)
{}

void CompPosition::update()
{
    x += dx;
    y += dy;

    //check bounds in here for now, but I will want to change this..
    if( x > 10 || x < -10 ) { dx = - dx; }
    if( y > 10 || y < -10 ) { dy = - dy; }
}

void CompPosition::init(float x, float y, float angle)
{
    this->x = x;
    this->y = y;
    this->angle = angle;
}
