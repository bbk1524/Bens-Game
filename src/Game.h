#ifndef GAME_H
#define GAME_H

#include "InputSystem.h"
#include "Definitions.h"
#include "Logger.h"
#include "Graphics.h"
#include "Timer.h"
#include "Config.h"

#include <memory>
#include <vector>
#include <string>

extern Logger logger;

class Entity;

class Game {
public:

    Game(int fps);
    Game(std::string config_file_path);
    //NOTE (bbkane): Need a destructor, even if empty
    ~Game();
    //gimme a frame
    void update();

    //gimme all da frames
    void run();

    bool is_valid() const;

// private:
    bool quit{ false };
    bool valid{ true };
    Input_System input_system;
    Graphics graphics;
    // Note (bkane): clang++ doesn't like this...
    // std::vector<std::unique_ptr<Entity>> entities;
    // clang++ friendly version
    std::vector<Entity*> entities;
    Timer fps_timer;
    int millisec_per_frame;
    Config config;
};

#endif
