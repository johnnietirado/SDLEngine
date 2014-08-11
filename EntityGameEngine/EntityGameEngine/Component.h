#ifndef COMPONENT_H
#define COMPONENT_H
#include "Structures.h"
#include "Message.h"
class Component
{
public:
	virtual void SendMessage(Message *message) = 0;
	virtual void Update(float dt) = 0;
	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;
	bool Active(void) const;

	ComponentID GetComponentID() { return mID; }
	void setOwner(GameObjectID ownerID) { mOwner = ownerID; }
protected:
	ComponentID mID;
	bool active;
	GameObjectID mOwner;
};

#endif

