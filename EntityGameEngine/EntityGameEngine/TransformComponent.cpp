#include "TransformComponent.h"


void TransformComponent::Initialize(void)
{
	pos.setX(0);
	pos.setY(0);
	mID = ComponentID::Transform;
}

void TransformComponent::SendMessage(Message* message)
{
}

void TransformComponent::Update(float dt)
{
	
}

void TransformComponent::Shutdown(void)
{
}

void TransformComponent::Translate(Vector2D v)
{
	pos += v;
}
