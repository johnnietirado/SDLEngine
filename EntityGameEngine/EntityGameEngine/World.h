#pragma once
#include "GameObject.h"
#include <vector>
class World
{
public:
	World();
	~World();

	void AddGameObject(GameObject* go);
	void RemoveGameObject(int index);
	std::vector<GameObject *> getGameObjects() { return mGameObjects; }
private:
	std::vector<GameObject *> mGameObjects;

};

