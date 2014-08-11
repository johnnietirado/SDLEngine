#pragma once

#include "Misc.h"
#include "Structures.h"
#include "Vector2D.h"

class Message
{
public:
	Message(MessageID id) : mID(id)
	{
	}

	~Message(){}

	virtual MessageID getID() { return mID; }

protected:
	MessageID mID;
};

class MoveMessage : public Message
{
public:
	MoveMessage(MessageID id, Vector2D movement) : Message(id), movementVector(movement)
	{

	}

	~MoveMessage(){}

	Vector2D  getMovement() { return movementVector; }
private:
	Vector2D movementVector;
};