#include "InputSystem.h"
#include "Timer.h"
#include "Constants.h"

#include <SDL.h>
#include <memory>


struct Pos
{
    float x;
    float y;
    Pos(float x, float y) : x(x), y(y)
    {}
};

struct Vel
{
    float x_pos;
    float y_pos;
    float x_neg;
    float y_neg;
    Vel(float x, float y)
        : x_pos(x), x_neg(x), y_pos(y), y_neg(y)
    {}
};

struct Shape
{
    SDL_Rect rect;
    Shape(int x, int y, int w, int h)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }
    void adjust_to_pos(const Pos & pos)
    {
        rect.x = static_cast<int>(pos.x) - rect.w / 2;
        rect.y = static_cast<int>(pos.y) - rect.h / 2; // Is it subtraction or addition?
    }
};

struct Entity
{
    Pos pos;
    Vel vel;
    Shape shape;

    Entity(Pos && pos, Vel && vel, Shape && shape)
        : pos(pos), vel(vel), shape(shape)
    {}
};

void update_renderer(SDL_Renderer *renderer, Pos & pos, Shape & shape)
{
    shape.adjust_to_pos(pos);
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &(shape.rect) );
}

void update_position(Input_System & input_system, Pos & pos, Vel & vel)
{
    if( input_system.get_event(game_event::UP) )
    {
        pos.y -= vel.y_neg;
    }
    if( input_system.get_event(game_event::DOWN) )
    {
        pos.y += vel.y_pos;
    }
    if( input_system.get_event(game_event::LEFT) )
    {
        pos.x -= vel.x_neg;
    }
    if( input_system.get_event(game_event::RIGHT) )
    {
        pos.x += vel.x_pos;
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

    Entity entity(Pos(G_WINDOW_WIDTH/2, G_WINDOW_HEIGHT/2),
        Vel(20, 20), Shape(0, 0, 30, 30));

    Timer timer;

    while (!input_sytem.get_event(game_event::QUIT))
    {
        input_sytem.update();

        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

        // Clear winow
        SDL_RenderClear( renderer );

        update_position(input_sytem, entity.pos, entity.vel);
        update_renderer(renderer, entity.pos, entity.shape);

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
