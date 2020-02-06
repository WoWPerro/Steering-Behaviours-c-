#pragma once
#include <string>
#include "SDL.h"
#include "Image.h"
#include "GameState.h"
#include "ListaT.h"

class GameState;

class Platform
{
private:
	SDL_Window* window;

public:
	int width;
	int height;
	float lastmouseX;
	float lastmouseY;
	static SDL_Renderer* renderer;
	Platform(std::string name);
	~Platform();
	void RenderClear();
	void RenderImage(Image* image, int x, int y, float angle);
	void RenderPresent();

	//std::vector <SDL_Event>& GetFrameEvents();
	ListaT<SDL_Event>& GetFrameEvents();
	void CheckEvent(GameState* obj, bool (GameState::* f)(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool* leftclick, float* mouseX, float* mouseY));
	void DrawRect(int x, int y, int w, int h);
	void DrawTriangle(int x, int y, int h, int b);
private:
	void RenderTexture(Image* image, int x, int y, double a);

};