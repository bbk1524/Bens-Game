#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

 #include "Logger.h"
 extern Logger logger;

#include "Definitions.h"
#include <map>
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
        //keys
        current_events[game_event::LEFT] = false;
        current_events[game_event::RIGHT] = false;
        current_events[game_event::UP] = false;
        current_events[game_event::DOWN] = false;
        current_events[game_event::ALT_LEFT] = false;
        current_events[game_event::ALT_RIGHT] = false;
        current_events[game_event::ALT_UP] = false;
        current_events[game_event::ALT_DOWN] = false;
        current_events[game_event::ACTION_ONE] = false;
        current_events[game_event::ACTION_TWO] = false;
        //mouse
        current_events[game_event::LEFT_MOUSE_DOWN] = false;
        current_events[game_event::RIGHT_MOUSE_DOWN] = false;
        //quit
        current_events[game_event::QUIT] = false;

        //do that for mouse buttons too
        tr_mouse.emplace(SDL_BUTTON_LEFT, game_event::LEFT_MOUSE_DOWN);
        tr_mouse.emplace(SDL_BUTTON_RIGHT, game_event::RIGHT_MOUSE_DOWN);

        //TODO: harden this drastically
        int num_joysticks = SDL_NumJoysticks();
        logger.log("Number of joysticks: ", num_joysticks);
        game_controller =  SDL_GameControllerOpen(0);
        logger.check(COND(!game_controller), "controller not found");

        return true;
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
        //alias function to make it shorter
        //TODO (bkane): is this slower? Should I use a #define?
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
                current_events[game_event::QUIT] = true;
                return;
            }

            //handle keys
            else if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
            {

                //set is_dwon to whether the key is being pressed
                bool is_down = event.type == SDL_KEYDOWN;

                //get the right game event, and map it to the bool
                current_events[tr_SDLK(event.key.keysym.sym)] = is_down;
            }


            //handle mouse buttons
            else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
            {
                bool is_down = event.type == SDL_MOUSEBUTTONDOWN;

                current_events[tr_mouse[event.button.button]] = is_down;
            }
            //handle gampad
            else if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
            {
                bool is_down = event.type == SDL_CONTROLLERBUTTONDOWN;

                // make sure the button is down before assigning a true to that map!
                //What the macro will expand to
                current_events[game_event::UP] = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_UP) && is_down;
#define MAKE_BUTTON_PRESS(g_event, SDL_cont_enum) current_events[game_event::g_event] = SDL_GameControllerGetButton(game_controller, SDL_cont_enum) && is_down
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
        return current_events[event_type];
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
    std::map<game_event, bool> current_events;
    SDL_Event event;
    //relying on the fact that an enum is implicitly converted to an int...
    //std::map<int, game_event> tr_key;
    std::map<int, game_event> tr_mouse;
    int mouse_x;
    int mouse_y;
    bool valid{ true };
    SDL_GameController *game_controller;
};

#endif
