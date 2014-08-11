#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Engine.h"

TextureManager* TextureManager::mInstance = NULL;

TextureManager* TextureManager::Instance()
{
	if(!mInstance)
		mInstance = new TextureManager;
	return mInstance;
}

bool TextureManager::Load(std::string filename, std::string id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());

	if(tempSurface == NULL)
	{
		printf("Error loading: %s \n", SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	if(texture != 0)
	{
		mTextureMap[id] = texture;
		return true;
	}
	printf("Error creating texture %s: %s \n", filename, SDL_GetError());
	return false;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, mTextureMap[id], &srcRect, &destRect, 0 , 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, mTextureMap[id], &srcRect, &destRect, 0 , 0, flip);
}

void TextureManager::clearFromTextureMap(std::string textureID)
{
	mTextureMap.erase(textureID);
}

void TextureManager::DrawRectangle(int x, int y, int w, int h, int r, int g, int b, SDL_Renderer* renderer)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, rect);
}
	
