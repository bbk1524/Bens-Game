#include "InputSystem.h"
#include "Timer.h"
#include "Constants.h"

#include <SDL.h>
#include <memory>


struct Entity
{
    SDL_Rect position;
    Entity()
    {
        position.x = 100;
        position.y = 100;
        position.w = 50;
        position.h = 50;
    }
};

void update_renderer(SDL_Renderer *renderer, SDL_Rect *position)
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, position );
}

void update_position(Input_System& input_system, SDL_Rect *position)
{
    constexpr int speed = 20;
    if( input_system.get_event(game_event::UP) )
    {
        position->y -= speed;
    }
    if( input_system.get_event(game_event::DOWN) )
    {
        position->y += speed;
    }
    if( input_system.get_event(game_event::LEFT) )
    {
        position->x -= speed;
    }
    if( input_system.get_event(game_event::RIGHT) )
    {
        position->x += speed;
    }
}

//VS2015 doesn't like SDL_main
#if defined(_MSC_VER) && (_MSC_VER == 1900)
# undef main
#endif // _MSC_VER == 1900

int main (int argc, char** argv)
{

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Bens Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        G_WINDOW_WIDTH,
        G_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Input_System input_sytem;
    input_sytem.init();
    input_sytem.update();

    Entity entity;

    Timer timer;

    while (!input_sytem.get_event(game_event::QUIT))
    {
        input_sytem.update();

        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

        // Clear winow
        SDL_RenderClear( renderer );

        update_position(input_sytem, &entity.position);
        update_renderer(renderer, &entity.position);

        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        // Lock the fps
        auto ticks = timer.get_ticks();
        if (ticks < 1000 / G_FRAMES_PER_SEC) {
            auto wait_time = 1000 / G_FRAMES_PER_SEC - ticks;
            SDL_Delay(wait_time);
        }
        timer.reset();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
