#pragma once

#include "GameObject.h"
#include "XMLParser.h"
#include <map>


class BaseCreator
{
public:
	GameObject* CreateGameObject(const char* file, GameObjectID id)
	{
		return XMLParser::Instance()->ParseGameObject(file, id);
	}
	~BaseCreator() {}


};

