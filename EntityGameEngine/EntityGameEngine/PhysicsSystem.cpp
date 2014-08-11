#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PlayerControllerComponent.h"
#include "InputHandler.h"
#include "Message.h"
#include <iostream>

void PhysicsSystem::Update(float dt, World* world)
{
	for (int i = 0; i < world->getGameObjects().size(); ++i)
	{
		if (world->getGameObjects()[i]->HasComponent(ComponentID::Transform))
		{
			world->getGameObjects()[i]->GetComponent<TransformComponent>(ComponentID::Transform).Update(dt);
		}
		if (world->getGameObjects()[i]->HasComponent(ComponentID::Controller))
		{
			world->getGameObjects()[i]->GetComponent<PlayerControllerComponent>(ComponentID::Controller).Update(dt);
		}
	}
}

void PhysicsSystem::Initialize()
{

}

void PhysicsSystem::SendMessage(Message* msg)
{

}

PhysicsSystem::~PhysicsSystem()
{
}

