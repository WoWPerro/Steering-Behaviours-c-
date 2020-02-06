#include "Platform.h"
#include "SDL.h"
#include <iostream>
#include "GameState.h"
#include "ListaT.h"

SDL_Renderer* Platform::renderer;

Platform::Platform(std::string name)
{
	width = 1920;
	height = 1080;
	/*width = 720;
	height = 480;*/

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init";
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN);
	if (window == nullptr)
	{
		std::cout << "CreateWindow";
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "CreateRenderer";
		SDL_Quit();
		return;
	}
}

void Platform::RenderClear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Platform::RenderPresent()
{
	SDL_RenderPresent(renderer);
}


void Platform::DrawRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

void  Platform::DrawTriangle(int x, int y, int h, int b)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y, x + (b/2), y-h);
	SDL_RenderDrawLine(renderer, x, y, x + b, y);
	SDL_RenderDrawLine(renderer, x + b, y, x + (b / 2), y - h);
}

void Platform::RenderImage(Image* image, int x, int y, float angle)
{
	RenderTexture(image, x, y, angle);
}

void Platform::RenderTexture(Image* image, int x, int y, double a)
{
	SDL_Rect srcrect;
	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = image->GetWidth();
	srcrect.h = image->GetHeight();
	SDL_RenderCopyEx(renderer, image->GetTexture()
		, NULL, &srcrect, a, NULL, SDL_FLIP_NONE);
}

Platform::~Platform()
{
}

ListaT<SDL_Event>& Platform::GetFrameEvents()
{
	//static std::vector<SDL_Event> frame_events;
	static ListaT<SDL_Event> frame_events;
	return frame_events;
}

void Platform::CheckEvent(GameState* obj, bool (GameState::* f)(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool *leftclick, float *mouseX, float *mouseY))
{
	SDL_Event e;
	ListaT<int> keysDown;
	ListaT<int> keysUp;
	bool _leftclick = false;
	float _mouseX = lastmouseX;
	float _mouseY = lastmouseY;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				keysDown.push_back(SDLK_LEFT);
			}
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				keysDown.push_back(SDLK_RIGHT);
			}
			if (e.key.keysym.sym == SDLK_UP)
			{
				keysDown.push_back(SDLK_UP);
			}
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				keysDown.push_back(SDLK_DOWN);
			}
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				keysDown.push_back(SDLK_SPACE);
			}
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				keysDown.push_back(SDLK_ESCAPE);
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				keysDown.push_back(SDLK_s);
			}
			if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				keysDown.push_back(SDLK_BACKSPACE);
			}
			break;


		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				keysUp.push_back(SDLK_LEFT);
			}
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				keysUp.push_back(SDLK_RIGHT);
			}
			if (e.key.keysym.sym == SDLK_UP)
			{
				keysUp.push_back(SDLK_UP);
			}
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				keysUp.push_back(SDLK_DOWN);
			}
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				keysUp.push_back(SDLK_SPACE);
			}
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				keysUp.push_back(SDLK_ESCAPE);
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				keysUp.push_back(SDLK_s);
			}
			if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				keysDown.push_back(SDLK_BACKSPACE);
			}
			break;

		case SDL_MOUSEMOTION:
			_mouseX = e.motion.x;
			lastmouseX = _mouseX;
			_mouseY = e.motion.y;
			lastmouseY = _mouseY;
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			SDL_MouseButtonEvent& b = e.button;
			if (b.button == SDL_BUTTON_LEFT)
			{
				_leftclick = true;
			}
		}
			
			break;
		case SDL_MOUSEBUTTONUP:
		{
			SDL_MouseButtonEvent& B = e.button;
			if (B.button == SDL_BUTTON_LEFT)
			{
				_leftclick = false;
			}
		}
			
			break;
		}
	}

	(obj->*f)(&keysDown, &keysUp, &_leftclick, &_mouseX, &_mouseY);
}