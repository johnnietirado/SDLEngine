#pragma once
#include "Structures.h"
#include "World.h"
class System
{
public:

	virtual void Update(float dt, World* world) = 0;

	virtual void Initialize(void) = 0;

	virtual void SendMessage(Message* msg) = 0;
	~System();

protected:

};

