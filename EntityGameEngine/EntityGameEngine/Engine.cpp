#include "Engine.h"
#include "DungeonGenerator.h"
#include <time.h>


Engine* Engine::mInstance = NULL;

Engine* Engine::Instance()
{
	if (!mInstance)
		mInstance = new Engine;
	return mInstance;
}

bool Engine::Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;

		//Init Window
		mWin = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (mWin != NULL)
		{
			printf("Window created succesfully\n");
			
			InputHandler::Instance()->Initialize();
			InputHandler::Instance()->InitializeJoysticks();
			Load();
			printf("Initialization Successful\n");
			isRunning = true;
			
			return true;
		}
		else
		{
			printf("Error Creating Window: %s\n", SDL_GetError());
			return false;
		}
	}
	else
	{
		isRunning = false;
		return false;
	}
}

void Engine::Load()
{
	world = new World();
	gof = new GameObjectFactory();
	timer = new GameTimer();
}

void Engine::RunGame()
{
	timer->Tick();
	InputHandler::Instance()->Update();
	for (int i = 0; i < mSystems.size(); ++i)
	{
		mSystems[i]->Update(timer->DeltaTime(), world);
	}
}

void Engine::AddSystem(System* system)
{
	system->Initialize();
	mSystems.push_back(system);
}

void Engine::Shutdown()
{
	isRunning = false;
}


