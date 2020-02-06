#include "Gif.h"

Gif::Gif()
{
	_vel = 1;
	//currentFrame = ImageList.get_at(index)->value;
}

Gif::Gif(bool loop)
{
	_vel = 1;
	//currentFrame = ImageList.get_at(index)->value;
	_loop = loop;
}

Gif::~Gif()
{

}

void Gif::update()
{
	if (SDL_TICKS_PASSED(SDL_GetTicks(), _lastFrameTime))
	{
		_lastFrameTime = SDL_GetTicks() + _vel;
		if (index == ImageList.size - 1)
		{
			if (_loop)
			{
				index = 0;
			}
			else
			{
				_finish = true;
			}
		}
		else
		{
			index++;
		}
	}
	currentFrame = ImageList.get_at(index)->value;
}

void Gif::SetVelocity(int vel)
{
	_vel = vel;
}

void Gif::AddImage(std::string i)
{
	image = new Image();
	image->LoadImage(i);
	ImageList.push_back(*image);
}