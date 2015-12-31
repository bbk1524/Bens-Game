#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

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
	~Input_System() = default;

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

		//translate SDL_Events of type key to Game_Events (not as fast as switch-case, but cleaner)
		//tr_key[SDLK_LEFT] = game_event::LEFT;
		//tr_key.emplace(SDLK_RIGHT, game_event::RIGHT);
		//tr_key.emplace(SDLK_LEFT, game_event::LEFT);
		//tr_key.emplace(SDLK_UP, game_event::UP);
		//tr_key.emplace(SDLK_DOWN, game_event::DOWN);
		//tr_key.emplace(SDLK_f, game_event::ACTION_ONE);
		//TODO: add the rest of my keys. 

		//do that for mouse buttons too
		tr_mouse.emplace(SDL_BUTTON_LEFT, game_event::LEFT_MOUSE_DOWN);
		tr_mouse.emplace(SDL_BUTTON_RIGHT, game_event::RIGHT_MOUSE_DOWN);

		return true;
	}

	game_event tr_SDLK(int SDLK)
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

	void update()
	{

		if (SDL_PollEvent(&event))
		{
			//handle the quit
			if (event.type == SDL_QUIT)
			{
				current_events[game_event::QUIT] = true;
			}

			//handle keys
			if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
			{

				//set is_dwon to whether the key is being pressed
				bool is_down = event.type == SDL_KEYDOWN;

				//get the right game event, and map it to the bool
				current_events[tr_SDLK(event.key.keysym.sym)] = is_down;
			}


			//handle mouse buttons
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				bool is_down = event.type == SDL_MOUSEBUTTONDOWN;

				current_events[tr_mouse[event.button.button]] = is_down;
			}

			//handle mouse motion
			if (event.type == SDL_MOUSEMOTION)
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
};

#endif