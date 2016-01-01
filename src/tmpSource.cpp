#include <SDL.h>
#include <iostream>

#undef main



int oldmain(int argc, int** argv)
{
    fprintf(stdout, "tmpSource activated!\n");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Event event;
    /* Other initializtion code goes here */
    
    SDL_GameController *ControllerHandles;

    int MaxJoysticks = SDL_NumJoysticks();
    fprintf(stderr, "Joysticks: %d\n", MaxJoysticks);
    for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
    {
        if (!SDL_IsGameController(JoystickIndex))
        {
            continue;
        }
        ControllerHandles = SDL_GameControllerOpen(JoystickIndex);
    }

    for (;;)
    {
        if (ControllerHandles != 0 && SDL_GameControllerGetAttached(ControllerHandles))
        {
            fprintf(stderr,"inloop\n");
            // NOTE: We have a controller with index ControllerIndex.
            bool Up = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_DPAD_UP);
            bool Down = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
            bool Left = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
            bool Right = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            bool Start = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_START);
            bool Back = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_BACK);
            bool LeftShoulder = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
            bool RightShoulder = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
            bool AButton = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_A);
            bool BButton = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_B);
            bool XButton = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_X);
            bool YButton = SDL_GameControllerGetButton(ControllerHandles, SDL_CONTROLLER_BUTTON_Y);

            Sint16 StickX = SDL_GameControllerGetAxis(ControllerHandles, SDL_CONTROLLER_AXIS_LEFTX);
            Sint16 StickY = SDL_GameControllerGetAxis(ControllerHandles, SDL_CONTROLLER_AXIS_LEFTY);

            if (AButton) { fprintf(stderr, "Abutton"); }
        }
        else
        {
            // TODO: This controller is note plugged in.
        }
    }

    SDL_GameControllerClose(ControllerHandles);

}