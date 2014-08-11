#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "Misc.h"
#include <string>
#include "Vector2D.h"


//Name Of The Specific Game Object
typedef unsigned int GameObjectID;

struct Animation
{
	AnimationID id;
	std::string texID;
	int width, height;
	int rowStart, colStart, numFrames, currentFrame = 0, animationSpeed;
	bool finished = false;

	void CheckIfFinished()
	{
		if (currentFrame >= numFrames)
			finished = true;
	}
};

#endif