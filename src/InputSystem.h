#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "Constants.h"

#include <array>
#include <SDL.h>


//Note, this class only registers input when the game window is open, NOT when only the console is up!

 class Input_System {
 public:
     Input_System()
     {
         mouse_x = 0;
         mouse_y = 0;
     }
     ~Input_System()
     {
         SDL_GameControllerClose(game_controller);
     }

    bool init()
    {
        game_controller =  SDL_GameControllerOpen(0);

        return true;
    }

    inline game_event tr_mouse(int sdl_mouse_button)
    {
        switch (sdl_mouse_button)
        {
            case SDL_BUTTON_LEFT: return game_event::LEFT_MOUSE_DOWN;
            case SDL_BUTTON_RIGHT: return game_event::RIGHT_MOUSE_DOWN;
            default: return game_event::OTHER;
        }
    }

    inline game_event tr_SDLK(int SDLK)
    {
        switch (SDLK) 
        {
        case SDLK_LEFT: return game_event::LEFT;
        case SDLK_RIGHT: return game_event::RIGHT;
        case SDLK_UP: return game_event::UP;
        case SDLK_DOWN: return game_event::DOWN;
        case SDLK_f: return game_event::ACTION_ONE;
        case SDLK_q: return game_event::QUIT;
        case SDLK_ESCAPE: return game_event::QUIT;
        default: return game_event::OTHER;
        }
    }

    inline game_event tr_SDL_GameControllerButton()
    {
        const auto& button = SDL_GameControllerGetButton;
        if (button(game_controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) { return game_event::UP; }
        else {return game_event::OTHER;}
    }

    void update()
    {

        if (SDL_PollEvent(&event))
        {
            //handle the quit
            if (event.type == SDL_QUIT)
            {
                // current_events[game_event::QUIT] = true;
                current_events_array[static_cast<int>(game_event::QUIT)] = true;
                return;
            }

            //handle keys
            else if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
            {

                //set is_dwon to whether the key is being pressed
                bool is_down = event.type == SDL_KEYDOWN;

                //get the right game event, and map it to the bool
                // current_events[tr_SDLK(event.key.keysym.sym)] = is_down;
                current_events_array[static_cast<int>(tr_SDLK(event.key.keysym.sym))] = is_down;
            }


            //handle mouse buttons
            else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
            {
                bool is_down = event.type == SDL_MOUSEBUTTONDOWN;

                // current_events[tr_mouse[event.button.button]] = is_down;
                current_events_array[static_cast<int>(tr_mouse(event.button.button))] = is_down;
            }
            //handle gampad
            else if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
            {
                bool is_down = event.type == SDL_CONTROLLERBUTTONDOWN;

#define MAKE_BUTTON_PRESS(g_event, SDL_cont_enum) current_events_array[static_cast<int>(game_event::g_event)] = SDL_GameControllerGetButton(game_controller, SDL_cont_enum) && is_down
                MAKE_BUTTON_PRESS(UP, SDL_CONTROLLER_BUTTON_DPAD_UP);
                MAKE_BUTTON_PRESS(DOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
                MAKE_BUTTON_PRESS(LEFT, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
                MAKE_BUTTON_PRESS(RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
                MAKE_BUTTON_PRESS(ACTION_ONE, SDL_CONTROLLER_BUTTON_A);
                MAKE_BUTTON_PRESS(ACTION_TWO, SDL_CONTROLLER_BUTTON_B);
#undef MAKE_BUTTON_PRESS
            }


            //handle mouse motion
            else if (event.type == SDL_MOUSEMOTION)
            {
                this->mouse_x = event.motion.x;
                this->mouse_y = event.motion.y;
            }


        }
    }

    bool get_event(game_event event_type)
    {
        // return current_events[event_type];
        return current_events_array[static_cast<int>(event_type)];
    }

    int get_mouse_x()
    {
        return mouse_x;
    }

    int get_mouse_y()
    {
        return mouse_y;
    }

    bool is_valid() const
    {
        return valid;
    }

private:
    SDL_Event event;
    int mouse_x;
    int mouse_y;
    bool valid{ true };
    SDL_GameController *game_controller;
    // starting to change this for speed!
    std::array<bool, static_cast<int>(game_event::SIZE)> current_events_array{};
};

#endif
