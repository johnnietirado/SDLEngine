
#ifndef TEXTURE_MANAGER_H

#define TEXTURE_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static TextureManager* Instance();
	void LoadTexturesFromFile(std::string filename);
	bool Load(std::string filename, std::string id, SDL_Renderer* renderer);
	void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void clearFromTextureMap(std::string textureID);
	void DrawRectangle(int x, int y, int w, int h, int r, int g, int b, SDL_Renderer* renderer);
protected:
	
private:
	std::map<std::string, SDL_Texture*> mTextureMap;
	static TextureManager* mInstance;
	TextureManager(){};
};

#endif

