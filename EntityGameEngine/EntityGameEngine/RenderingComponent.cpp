#include "RenderingComponent.h"
#include "Engine.h"
#include "TransformComponent.h"


void RenderingComponent::SendMessage(Message *message)
{

}

void RenderingComponent::Render(SDL_Renderer* renderer)
{
	posToRender.setX(Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).getPosX());
	posToRender.setY(Engine::Instance()->getWorld()->getGameObjects()[mOwner]->GetComponent<TransformComponent>(ComponentID::Transform).getPosY());

	TextureManager::Instance()->DrawFrame(
		animations[currentAnimation]->texID,
		posToRender.getX(), posToRender.getY(),
		animations[currentAnimation]->width,
		animations[currentAnimation]->height,
		animations[currentAnimation]->rowStart,
		animations[currentAnimation]->currentFrame,
		renderer);
}

void RenderingComponent::Initialize(void)
{
	posToRender.setX(0);
	posToRender.setY(0);
	
	mID = ComponentID::Renderer;
	if (animations.size() > 0)
		currentAnimation = animations.begin()->first;
	else
		currentAnimation = AnimationID::NONE;
	animations[currentAnimation]->currentFrame = 0;

}

void RenderingComponent::Shutdown(void)
{

}

void RenderingComponent::Update(float dt)
{
	animations[currentAnimation]->currentFrame = int(((SDL_GetTicks() / (1000 / animations[currentAnimation]->animationSpeed) % animations[currentAnimation]->numFrames)));
}
