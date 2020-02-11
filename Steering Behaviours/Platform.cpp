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

void  Platform::DrawTriangle(float x, float y, float h, float b)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y, x + (b / 2), y - h); //punta
	SDL_RenderDrawLine(renderer, x, y, x + b, y); //base
	SDL_RenderDrawLine(renderer, x + b, y, x + (b / 2), y - h); //punta
}

void Platform::DrawTriangle(float x, float y, float h, float b, int R, int B, int G)
{
	SDL_SetRenderDrawColor(renderer, R, G, B, 0xFF);
	SDL_RenderDrawLine(renderer, x, y, x + (b / 2), y - h); //punta
	SDL_RenderDrawLine(renderer, x, y, x + b, y); //base
	SDL_RenderDrawLine(renderer, x + b, y, x + (b / 2), y - h); //punta
}


void Platform::DrawVector(float x, float y, float v1, float v2, int R, int G, int B)
{
	SDL_SetRenderDrawColor(renderer, R, G, B, 0xFF);
	SDL_RenderDrawLine(renderer, x, y, v1, v2); //punta
}

void  Platform::DrawTriangle(float x, float y, float h, float b, Vector2 direction)
{
	direction.Normalize();
	float angle1;
	angle1 = direction.GetX();
	float dir = direction.length();
	float rot = acos(angle1 / dir);

	Vector2 nh;
	nh.SetValue(0, h/2);
	Vector2 nb;
	nb.SetValue(b/2, -h/2);
	Vector2 nx;
	nx.SetValue(-b / 2, -h / 2);

	float newx = ((nh.GetX() * cos(angle1)) + (nh.GetY() * sin(angle1))) + x;
	float newy = (-(nh.GetX() * sin(angle1)) + (nh.GetY() * cos(angle1))) + y;
	float newx2 = (((nb.GetX()) * cos(angle1)) + ((nb.GetY()) * sin(angle1))) + x;
	float newy2 = ((-(nb.GetX()) * sin(angle1)) + ((nb.GetY()) * cos(angle1))) + y;
	float newx3 = (((nx.GetX()) * cos(angle1)) + ((nx.GetY()) * sin(angle1))) + x;
	float newy3 = ((-(nx.GetX()) * sin(angle1)) + ((nx.GetY()) * cos(angle1))) + y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, newx, newy, newx2, newy2); //punta
	SDL_RenderDrawLine(renderer, newx, newy, newx3, newy3); //base
	SDL_RenderDrawLine(renderer, newx3, newy3, newx2, newy2); //punta
}

void Platform::DrawCircle(float xc, float yc, float r, int R, int B, int G)
{
	float p = 1 - r;
	yc = -yc;
	float x = 0;
	float y = r;

	do
	{
		//Aprovechar simetría del círculo
		//SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x40, 0xFF);
		SDL_SetRenderDrawColor(renderer, R, G, B, 0xFF);
		SDL_RenderDrawPoint(renderer, x + xc, y + yc);
		SDL_RenderDrawPoint(renderer, x + xc, -y + yc);
		SDL_RenderDrawPoint(renderer, -x + xc, y + yc);
		SDL_RenderDrawPoint(renderer, -x + xc, -y + yc);
		SDL_RenderDrawPoint(renderer, y + xc, x + yc);
		SDL_RenderDrawPoint(renderer, y + xc, -x + yc);
		SDL_RenderDrawPoint(renderer, -y + xc, x + yc);
		SDL_RenderDrawPoint(renderer, -y + xc, -x + yc);
		if (p <= 0)
		{
			x++;
			p = p + (2 * x) + 3;
		}
		else if (p > 0)
		{
			x++;
			y = y - 1;
			p = (2 * x) - (2 * y) + 5 + p;
		}
	} while (x <= y);
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