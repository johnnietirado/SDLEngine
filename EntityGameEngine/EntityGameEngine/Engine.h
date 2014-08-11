#pragma once
#include "System.h"
#include "World.h"
#include "GameObjectFactory.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameTimer.h"
#include <vector>
#include "InputHandler.h"
#include "DungeonGenerator.h"

class Engine
{
public:
	static Engine* Instance();
	bool Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void Load();
	void RunGame();
	void AddSystem(System* system);
	void Shutdown();
	bool isGameRunning() { return isRunning; }
	World* getWorld() { return world; }
	GameObjectFactory* getGOF() { return gof; }
	SDL_Window* getWin() { return mWin; }
	SDL_Surface* getWinSurface() { return winSurface; }
	//MapCreator* getMapCreator(){ return mc; }

private:
	std::vector<System *> mSystems;
	bool isRunning;

	World* world;
	GameObjectFactory* gof;
	SDL_Window* mWin;
	SDL_Surface* winSurface;
	GameTimer* timer;
	//MapCreator* mc;
	static Engine* mInstance;

	Engine(){}
};

