#pragma once
#include "Component.h"
class HealthComponent :
	public Component
{
public:
	void SendMessage(Message *message);
	void Update(float dt);
	void Initialize(void);
	void Load(int h, int mh);
	void Shutdown(void);

	int GetHealth(){ return health; }
	void SetHealth(int newHealth) { health = newHealth; }
	void SetMaxHealth(int newMaxHealth) { maxHealth = newMaxHealth; }

private:
	int health, maxHealth;
};

