#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <vector>
#include "Structures.h"
#include "Message.h"

class Component;

class GameObject
{
public:
	GameObject();
	void SendMessage(Message *msg);
	bool HasComponent(ComponentID id) const;
	void AddComponent(ComponentID id, Component* component);
	void Update(float dt);
	
	template<class T>
	T& GetComponent(ComponentID id)
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (((int)mComponents[i]->GetComponentID() & mComponentIDs) & (int)id)
				return (*dynamic_cast<T*>(mComponents[i]));
		}
	}

	// A Handle is a unique identifier to this object
	GameObjectID GetID(void) const;

	//Check to see if the Object is Active
	bool Active(void) const;
	void setTag(Tags newTag){ tag = newTag; }
	Tags getTag(){ return tag; }
	void setID(GameObjectID ID) { mID = ID; }
	bool Load();

private:
	GameObjectID mID;
	std::vector<Component*> mComponents;
	int mComponentIDs;
	bool active;
	Tags tag;

	//GameObject();
	~GameObject();
};

#endif

