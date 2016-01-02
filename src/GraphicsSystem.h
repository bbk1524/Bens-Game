#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "Logger.h"
extern Logger logger;
#include "Entity.h"
#include "CompPosition.h"
#include "BoxUtils.h"
#include <vector>

#include <SDL.h>
#include <string>
#include <SDL_image.h>

//This class just gives me a window.That's all it does. I need a screen class to draw my boxes

class Graphics_System {
public:
    Graphics_System()
    {
        window = nullptr;
        renderer = nullptr;
    }

    ~Graphics_System() = default;


    //TODO: make this actually check for errors
    bool init(std::string window_name, int window_width, int window_height)
    {
        // move the SDL_Init stuff to Game so I can add
        // systems in order

        this->width = window_width;
        //NOTE (bkane): height is flipped
        this->height = window_height;

        window = SDL_CreateWindow(
            window_name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
        return true;
    }

    //I'm assuming that this is the last system to end;
    bool destroy()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return true;
    }

    void begin()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); //TODO: get this back...
    }

    void update(std::vector<Entity*> & entities, std::vector<Box> boxes)
    {
        for (auto &box : boxes)
        {
            logger.log(box.name);
            SDL_Rect r;
            r.x = box.x1;
            r.y = box.y1;
            r.w = box.x2 - box.x1;
            r.h = box.y2 - box.y1;
            if (box.name == "Window")
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else if (box.name == "Outer Left")
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            else if (box.name == "Inner Left")
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            }
            else if (box.name == "Bottom")
            {
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
            }
            else if (box.name == "Game")
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
            SDL_RenderFillRect(renderer, &r);
        }

        for (auto &en : entities)
        {
            if (en->type == "DrawMe")
            {
                // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
                SDL_Rect r;
                r.x = p_to_r_x(en->get_component<CompPosition>()->x);
                //Y is flipped..
                r.y = p_to_r_y(en->get_component<CompPosition>()->y);
                r.w = 50;
                r.h = 50;
                if (r.x + r.w > width) { r.x = width - 50; }
                if (r.y + r.h > height) { r.y = height - 50; }

                // Set render color to blue ( rect will be rendered in this color )
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

                // Render rect
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }


    void present()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Renderer * get_renderer() {
        return renderer;
    }
    SDL_Window* get_window() {
        return window;
    }

    bool is_valid() const
    {
        return valid;
    }

    //Physics to render coordinates
    //This depends on the physics coords in [-10, 10]
    int p_to_r_x(float x)
    {
        int b = int((width + 0) / 2);
        int m = int((0 - width) / (-20));
        return (int)(m * x + b);
    }

    inline int p_to_r_y(float y)
    {
        int b = int((height + 0) / 2);
        int m = int((0 - height) / (-20));
        return (int)(m * y + b);
    }
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool valid{ true };
    int height;
    int width;
};

#endif
