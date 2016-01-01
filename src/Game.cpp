#include "Game.h"

#include "Logger.h"
extern Logger logger;

#include "Entity.h"
#include "CompPosition.h"
#include "Timer.h"

#include <thread>
#include <chrono>

Game::Game(int fps)
{
    millisec_per_frame = static_cast<int>(1000 / fps);
    logger.log("ms per frame: ", millisec_per_frame);
    bool init = input_system.init();
    logger.check(COND(init), FILE_INFO);
    //bkane: Windows needs a vector of pointers
    // entities.push_back(std::make_unique<Entity>("TestComponent", this));
    // auto ent = std::make_unique<Entity>("Unknown", this);
    // ent->add_component<CompPosition>(1.f, 1.f, 1.f);
    // entities.push_back(std::move(ent));
    // entities.push_back(Entity("TestComponent", this));
    auto ent = new Entity("DrawMe", this);
    ent->add_component<CompPosition>(1.f, 1.f, 1.f);
    entities.push_back(ent);
    entities.push_back(new Entity("TestComponent", this));
    logger.log(this->is_valid(), "Game initialized!");

}

//NOTE (bbkane): need a destructor, even an empty one
Game::~Game()
{
    while(!entities.empty())
    {
        delete entities.back();
        entities.pop_back();
    }
}

void Game::update()
{
    input_system.update();
    quit = input_system.get_event(game_event::QUIT);

    //check if in menu

    //Print Input System's Output (undeffed until I need it...)
#define PRINT_EVENT(EVENT) if (input_system.get_event(game_event::EVENT)) { logger.log(#EVENT);}
#ifdef PRINT_EVENT
    PRINT_EVENT(UP);
    PRINT_EVENT(DOWN);
    PRINT_EVENT(LEFT);
    PRINT_EVENT(RIGHT);
    PRINT_EVENT(ACTION_ONE);
    PRINT_EVENT(ACTION_TWO);
    PRINT_EVENT(OTHER);
    PRINT_EVENT(LEFT_MOUSE_DOWN);
    PRINT_EVENT(RIGHT_MOUSE_DOWN);
    PRINT_EVENT(QUIT);
#endif
#undef PRINT_EVENT
    logger.log(input_system.get_mouse_x(), input_system.get_mouse_y());
    for (auto & e : entities)
    {
        e->update();
        // e.update();
    }

    graphics.draw(entities);
}

void Game::run()
{
    while (!quit)
    {
        fps_timer.reset();
        update();
        int milliseconds = fps_timer.get_ticks();
        //logger.log(FILE_INFO, milliseconds);
        //There is a HUGE input lag here
        if (!quit && milliseconds < millisec_per_frame)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(millisec_per_frame - milliseconds));
        }

    }
}

bool Game::is_valid() const
{
    return valid;
}

