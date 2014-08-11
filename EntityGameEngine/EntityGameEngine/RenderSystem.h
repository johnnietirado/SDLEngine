#pragma once
#include "System.h"
#include <SDL.h>
class RenderSystem :
	public System
{
public:
	void Update(float dt, World* world);

	void Initialize(void);

	void SendMessage(Message* msg);

	void Load();
	~RenderSystem();

private:
	SDL_Renderer* mRenderer;
};

