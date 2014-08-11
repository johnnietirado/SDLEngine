#pragma once
#include "Component.h"
#include "TextureManager.h"
class RenderingComponent : public Component
{
public:
	void SendMessage(Message *message);
	void Update(float dt);
	void Initialize(void);
	void Shutdown(void);

	void Render(SDL_Renderer* renderer);

	void AddAnimation(AnimationID id, Animation* animation)
	{
		animations[id] = animation;
	}

	void ChangeAnimation(AnimationID newID)
	{
		if (currentAnimation == newID)
			return;
		if (animations.count(newID) > 0)
			currentAnimation = newID;
	}

private:
	std::string textureID;
	Vector2D posToRender;
	AnimationID currentAnimation;

	std::map<AnimationID, Animation*> animations;
};

