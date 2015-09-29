#include "Game.h"
#include "Definitions.h"
#include "Logger.h"


#include <SDL.h>
#include <SDL_image.h>

//undef main for VS2015 so SDL_main won't be called
//TODO: check if this actually hurts anything...
#if (_MSC_VER == 1900)
# undef main
#endif

//GLobal logger. Files which use this need 'extern Logger logger;' at their top
Logger logger;

int main (int argc, char** argv)
{
	//init libraries at the top level to avoid game system dependencies and because I'm using SDL_main anyway
	int init_return = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	logger.check(COND(init_return == 0), FILE_INFO, SDL_GetError());

	init_return = IMG_Init(IMG_INIT_PNG);
	logger.check(COND((init_return & IMG_INIT_PNG) == IMG_INIT_PNG), FILE_INFO, IMG_GetError());

	Game game;
	game.run();

	//stop libraries
	IMG_Quit();
	SDL_Quit();

	return 0;
}
