#include "HealthComponent.h"


void HealthComponent::Initialize(void)
{
	health = 0;
	mID = ComponentID::Transform;
}

void HealthComponent::SendMessage(Message* message)
{

}

void HealthComponent::Update(float dt)
{
}

void HealthComponent::Shutdown(void)
{
}

void HealthComponent::Load(int h, int mh)
{
	health = h;
	maxHealth = mh;
}



