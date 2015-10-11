#include "TestComponent.h"
#include "Logger.h"
#include "Entity.h"
extern Logger logger;

TestComponent::TestComponent(Entity * owner)
	: Component(owner)
{}

void TestComponent::update()
{
	a++;
	logger.log(get_owner()->game->is_valid());
}

void TestComponent::init()
{
}

