#pragma once

#include <SDL.h>
#include <string>

std::string get_base_path();

const std::string base_path = get_base_path();

//global variables yay!

const int G_WINDOW_WIDTH = 800; //TODO: change this to read from an ini file. Maybe make it a field of Screen?
const int G_WINDOW_HEIGHT = 600;

enum class game_event: int
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ALT_LEFT,
    ALT_RIGHT,
    ALT_UP,
    ALT_DOWN,
    ACTION_ONE,
    ACTION_TWO,
    LEFT_MOUSE_DOWN,
    RIGHT_MOUSE_DOWN,
    QUIT,
    OTHER, //Any other key. Put here to shut the warnings in InputSystem::tr_SDLK up
    SIZE
};

//TODO (bbkane): replace entity.type with this. When I konw what type of entities I want...
enum class entity_type
{
    TEST
};

