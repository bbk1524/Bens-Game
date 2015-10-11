#ifndef GAME_H
#define GAME_H

#include "InputSystem.h"
#include "Definitions.h"
#include "Logger.h"
#include "Graphics.h"

class EntityManager;

#include <memory>

extern Logger logger;

class Game {
public:

	Game();
	~Game();
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
	std::unique_ptr<EntityManager> entity_manager{ nullptr };
};

#endif 
