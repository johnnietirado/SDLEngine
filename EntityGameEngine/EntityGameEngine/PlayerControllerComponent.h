#pragma once
#include "Component.h"
class PlayerControllerComponent : public Component

{
public:

	void SendMessage(Message *message);
	void Update(float dt);
	void Initialize(void);
	void Load();
	void Shutdown(void);
};

