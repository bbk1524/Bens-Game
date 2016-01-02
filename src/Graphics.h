#pragma once

#include "GraphicsSystem.h"
#include "BoxUtils.h"
#include "Definitions.h"
#include "Entity.h"
#include <vector>

// This class is small now, but it will eventually do boxes

class Graphics
{
    public:
        Graphics()
        {
            //TODO (bkane): read from an init file
            graphics_system.init("Pure Awesome", 500, 400);
            boxes = make_boxes_from_config(base_path + "config/layout.xml", 500, 400);

        }

        ~Graphics()
        {
            graphics_system.destroy();
        }

        void draw(std::vector<Entity*> & entities)
        {
            graphics_system.begin();

            //update renderer here
            graphics_system.update(entities, boxes);

            graphics_system.present();
        }

        std::vector<Box> boxes;
        Graphics_System graphics_system;
};
