#include "World.h"


World::World()
{
}


World::~World()
{
}

void World::AddGameObject(GameObject* go)
{
	mGameObjects.push_back(go);
}

void World::RemoveGameObject(int index)
{
	//mGameObjects.erase(mGameObjects.begin + index);
}
