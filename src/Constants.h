#pragma once

enum class game_event : int
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


constexpr int G_WINDOW_WIDTH = 640;
constexpr int G_WINDOW_HEIGHT = 480;
constexpr int G_FRAMES_PER_SEC = 60;
