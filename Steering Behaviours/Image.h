#pragma once
#include "SDL.h"
#include <iostream>

class Image
{
private:
	SDL_Texture* image;
	std::string name;
	int w;
	int h;
public:
	void LoadImage(std::string name);
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
};