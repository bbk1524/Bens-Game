#include "Game.h"

#include "Logger.h"
extern Logger logger;

#include "Entity.h"
#include "CompPosition.h"

Game::Game()
{
    bool init = input_system.init();
    logger.check(COND(init), FILE_INFO);
    //bkane: Windows needs a vector of pointers
    // entities.push_back(std::make_unique<Entity>("TestComponent", this));
    // auto ent = std::make_unique<Entity>("Unknown", this);
    // ent->add_component<CompPosition>(1.f, 1.f, 1.f);
    // entities.push_back(std::move(ent));
    // entities.push_back(Entity("TestComponent", this));
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
    PRINT_EVENT(OTHER);
    PRINT_EVENT(LEFT_MOUSE_DOWN);
    PRINT_EVENT(RIGHT_MOUSE_DOWN);
    PRINT_EVENT(QUIT);
#endif
#undef PRINT_EVENT

    for (auto & e : entities)
    {
        e->update();
        // e.update();
    }

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

