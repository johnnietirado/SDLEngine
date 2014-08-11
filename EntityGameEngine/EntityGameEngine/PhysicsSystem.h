#pragma once
#include "System.h"
#include "Structures.h"

class PhysicsSystem :
	public System
{
public:

	void Update(float dt, World* world);
	void Initialize(void);
	void SendMessage(Message* msg);

	~PhysicsSystem();
};

