#include "Engine.h"
#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "PhysicsSystem.h"
#include <stdlib.h>
#include <iostream>
#include "RenderSystem.h"
#include "XMLParser.h"

int main(int argc, char *args[])
{
	
	Engine::Instance()->Initialize("SDL Engine", 100, 100, 640, 480, false);
	Engine::Instance()->AddSystem(new PhysicsSystem());
	Engine::Instance()->AddSystem(new RenderSystem());
	Engine::Instance()->getGOF()->RegisterType("Wall", "test.xml");
	Engine::Instance()->getGOF()->RegisterType("Castle", "tile.xml");
	Engine::Instance()->getWorld()->AddGameObject(Engine::Instance()->getGOF()->Create("Wall"));
	
	while (Engine::Instance()->isGameRunning())
	{
		Engine::Instance()->RunGame();
		
	}
	SDL_Quit();
	return 0;
}