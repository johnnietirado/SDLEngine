#include "GameObject.h"
#include "Component.h"

void GameObject::SendMessage(Message *msg)
{

}

bool GameObject::HasComponent(ComponentID id) const
{
	if ((mComponentIDs & (int)id) == (int)id)
		return true;
	return false;
}

void GameObject::AddComponent(ComponentID id, Component* component)
{
	mComponentIDs |= (int)id;
	mComponents.push_back(component);
}

void GameObject::Update(float dt)
{

}

GameObjectID GameObject::GetID(void) const
{
	return mID;
}

GameObject::GameObject()
{
	mComponentIDs = 0;
	tag = Tags::NONE;
}

GameObject::~GameObject()
{
}
