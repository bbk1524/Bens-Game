#ifndef GAME_H
#define GAME_H

#include "InputSystem.h"
#include "Definitions.h"
#include "Logger.h"
#include "Graphics.h"

#include <memory>
#include <vector>

extern Logger logger;

class Entity;

class Game {
public:

    Game();
    //NOTE (bbkane): Need a destructor, even if empty
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
    // Note (bkane): clang++ doesn't like this...
    std::vector<std::unique_ptr<Entity>> entities;
};

#endif
