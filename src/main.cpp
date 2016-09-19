#include "InputSystem.h"

#include <SDL.h>
#include <memory>

const int G_WINDOW_WIDTH = 640;
const int G_WINDOW_HEIGHT = 480;

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
    if( input_system.get_event(game_event::UP) )
    {
        position->y--;
    }
    if( input_system.get_event(game_event::DOWN) )
    {
        position->y++;
    }
    if( input_system.get_event(game_event::LEFT) )
    {
        position->x--;
    }
    if( input_system.get_event(game_event::RIGHT) )
    {
        position->x++;
    }
}

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
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    Input_System input_sytem;
    input_sytem.init();
    input_sytem.update();

    Entity entity;

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

        // Wait for 5 sec
        // SDL_Delay( 5000 );
    }


    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
