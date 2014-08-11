#ifndef MISC_H
#define MISC_H
#include <string>

enum MessageID {
	HELLO,
	GOODYE
};

enum class Tags
{
	NONE = 0, // 0
	PLAYER = 1 << 0, // 1
	TILE = 1 << 1 // 2
};

//Mask of the Specific Component
enum class ComponentID
{
	Transform = 1 << 0, // 1
	Renderer = 1 << 1, // 2
	Health = 1 << 2, // 4
	Controller = 1 << 3 // 8
};

enum class AnimationID
{
	NONE = 0,
	IDLE = 1,
	RUNNING = 2
};

enum Mouse
{
	LEFT = 0,
	RIGHT = 1,
	CENTER = 2
};



#endif