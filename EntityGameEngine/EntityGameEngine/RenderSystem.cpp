#include "RenderSystem.h"
#include "Engine.h"
#include "TextureManager.h"
#include "RenderingComponent.h"


void RenderSystem::Update(float dt, World* world)
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);
	for (int i = 0; i < world->getGameObjects().size(); ++i)
	{
		if (world->getGameObjects()[i]->HasComponent(ComponentID::Renderer))
		{
			world->getGameObjects()[i]->GetComponent<RenderingComponent>(ComponentID::Renderer).Update(dt);
			world->getGameObjects()[i]->GetComponent<RenderingComponent>(ComponentID::Renderer).Render(mRenderer);
		}
	}

	SDL_RenderPresent(mRenderer);
}

void RenderSystem::Initialize(void)
{
	mRenderer = SDL_CreateRenderer(Engine::Instance()->getWin(), -1, 0);

	if (mRenderer != NULL)
	{
		printf("Renderer created succesfully\n");
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	}
	else
	{
		printf("Error Creating Renderer: %s\n", SDL_GetError());
	}
	Load();
}

void RenderSystem::SendMessage(Message* msg)
{

}

void RenderSystem::Load()
{
	XMLParser::Instance()->LoadTexturesFromFile("Textures.xml", mRenderer);
}

RenderSystem::~RenderSystem()
{
}
