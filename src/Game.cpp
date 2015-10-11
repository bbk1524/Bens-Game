#include "Game.h"

#include "EntityManager.h"

#include "Logger.h"
extern Logger logger;

Game::Game()
{
	this->entity_manager = std::make_unique<EntityManager>(this);
	bool init = input_system.init();
	logger.check(COND(init), FILE_INFO);
	entity_manager->init(); //This breaks everything...
}

Game::~Game()
{
}

void Game::update()
{
	input_system.update();
	quit = input_system.get_event(game_event::QUIT);

	//check if in menu

	//Print Input System's Output (undeffed until I need it...)
#define PRINT_EVENT(EVENT) if (input_system.get_event(game_event::EVENT)) { logger.log(#EVENT);}
	//#undef PRINT_EVENT
#ifdef PRINT_EVENT
	PRINT_EVENT(UP);
	PRINT_EVENT(DOWN);
	PRINT_EVENT(LEFT);
	PRINT_EVENT(RIGHT);
	PRINT_EVENT(ACTION_ONE);
	PRINT_EVENT(OTHER);
	PRINT_EVENT(LEFT_MOUSE_DOWN);
	PRINT_EVENT(RIGHT_MOUSE_DOWN);
	PRINT_EVENT(QUIT);
#endif
#undef PRINT_EVENT

	entity_manager->update(this);
	//entity_manager.update();

	graphics.draw();
}

void Game::run()
{
	while (!quit)
	{
		update();
	}
}

bool Game::is_valid() const
{
	return valid;
}

