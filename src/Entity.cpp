#include "Entity.h"
#include "Component.h"

#include "TestComponent.h"

#include <memory>


//How the heck am I supposed to pass stuff to the 
//init functions?
//In my final, I passed in a Game* and an x,y,angle

//I want to use the standard system of each component having only data, and making "Systems" which read and write to the components on update
Entity::Entity(std::string type)
	: type(type)
{
	if (type == "TestComponent")
	{
		add_component<TestComponent>();
	}
	
}

void Entity::update()
{
	for (auto& c : components)
	{
		c->update();
	}
}