#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "Engine.h"
#include "InputHandler.h"


void PlayerControllerComponent::SendMessage(Message *message)
{

}

void PlayerControllerComponent::Update(float dt)
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).Translate(Vector2D(0, -1 * dt));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).Translate(Vector2D(1 * dt, 0));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).Translate(Vector2D(-1 * dt, 0));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).Translate(Vector2D(0, 1 * dt));
	}
}

void PlayerControllerComponent::Initialize(void)
{
	mID = ComponentID::Controller;
}

void PlayerControllerComponent::Load()
{

}

void PlayerControllerComponent::Shutdown(void)
{

}

