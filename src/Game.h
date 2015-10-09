#ifndef GAME_H
#define GAME_H

//#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Definitions.h"
#include "Logger.h"
#include "Graphics.h"
#include "Entity.h"

//class EntityManager;
#include "EntityManager.h"

extern Logger logger;

class Game {
public:

	Game();

	//gimme a frame
	void update();

	//gimme all da frames
	void run();

	bool is_valid() const;

private:
	bool quit{ false };
	bool valid{ true };
	Input_System input_system;
	Graphics graphics;
	EntityManager entity_manager;
};

#endif 
