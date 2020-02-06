#pragma once
#include "ListaT.h"
#include "Image.h"

class Gif
{
public:
	Gif();
	Gif(bool loop);
	~Gif();
	void update();
	void SetVelocity(int vel);
	Image currentFrame;
	void AddImage(std::string i);
private:
	Image* image;
	ListaT<Image> ImageList;
	int index = 0;
	Uint32 _lastFrameTime = SDL_GetTicks() + _vel;;
	int _vel;
	bool _finish = false;
	bool _loop = false;
};