#include "TestComponent.h"
#include "Logger.h"

extern Logger logger;

TestComponent::TestComponent(Entity * owner)
	: Component(owner)
{}

void TestComponent::update()
{
	a++;
}

void TestComponent::init()
{
}

