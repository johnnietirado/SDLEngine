#pragma once
#include "BaseCreator.h"
#include <iostream>

class GameObjectFactory
{
public:
	GameObjectFactory() { curActorId = 0; }

	bool RegisterType(char* typeID, const char* file)
	{
		std::map<char*, const char*>::iterator it = mCreators.find(typeID);

		if (it != mCreators.end())
		{
			//Already Registered Creator
			return false;
		}

		mCreators[typeID] = file;
		return true;
	}

	GameObject* Create(char* typeID)
	{
		std::map<char*, const char*>::iterator it = mCreators.find(typeID);
		if (it == mCreators.end())
		{
			std::cout << "Could not find type" << typeID << std::endl;
			return NULL;
		}

		BaseCreator* creator = new BaseCreator();
		return creator->CreateGameObject((*it).second, curActorId++);
	}

private:
	std::map<char*, const char*> mCreators;
	GameObjectID curActorId;
};

