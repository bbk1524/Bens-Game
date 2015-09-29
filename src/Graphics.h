#pragma once

#include "GraphicsSystem.h"

class Graphics
{
public:
	Graphics()
	{
		graphics_system.init("Test", 800, 600);
	}

	~Graphics()
	{
		graphics_system.destroy();
	}

	void draw()
	{
		graphics_system.begin();

		//update renderer here

		graphics_system.present();
	}

	Graphics_System graphics_system;
};