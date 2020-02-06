#include "Image.h"
#include "SDL_image.h"
#include "Platform.h"
void Image::LoadImage(std::string name)
{
	this->name = name;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	w = loadedSurface->w;
	h = loadedSurface->h;
	image = SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface);
}

SDL_Texture* Image::GetTexture()
{
	return image;
}
int Image::GetWidth()
{
	return w;
}

int Image::GetHeight()
{
	return h;
}