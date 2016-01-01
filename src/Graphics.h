#pragma once

#include "GraphicsSystem.h"
#include "Entity.h"
#include <vector>

// This class is small now, but it will eventually do boxes

class Graphics
{
    public:
        Graphics()
        {
            //TODO (bkane): read from an init file
            graphics_system.init("Pure Awesome", 400, 400);
        }

        ~Graphics()
        {
            graphics_system.destroy();
        }

        void draw(std::vector<Entity*> & entities)
        {
            graphics_system.begin();

            //update renderer here
            graphics_system.update(entities);

            graphics_system.present();
        }

        Graphics_System graphics_system;
};
