#ifndef GAME_H
#define GAME_H

//Print Input System's Output (undeffed until I need it...)
#define PRINT_EVENT(EVENT) if (input_system.get_event(game_event::EVENT)) { logger.log(#EVENT);}
//#undef PRINT_EVENT

//#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Definitions.h"
#include "Logger.h"
#include "Graphics.h"

extern Logger logger;


class Game {
public:

	Game()
	{
		bool init = input_system.init();
		logger.check(COND(init), FILE_INFO);
	}
	~Game()
	{

	}

	//gimme a frame
	void update()
	{
		input_system.update();
		if (input_system.get_event(game_event::QUIT))
		{
			quit = true;
		}

#ifdef PRINT_EVENT
		PRINT_EVENT(UP);
		PRINT_EVENT(DOWN);
		PRINT_EVENT(LEFT);
		PRINT_EVENT(RIGHT);
		PRINT_EVENT(ACTION_ONE);
		PRINT_EVENT(OTHER);
#endif

		draw();
	}

	void draw()
	{
		graphics.draw();
	}

	//gimme all da frames
	void run()
	{
		while (!quit)
		{
			update();
		}
	}

	bool is_valid() const
	{
		return valid;
	}

private:
	bool quit{ false };
	bool valid{ true };
	Input_System input_system;
	Graphics graphics;
};

#endif 
