#pragma once
#include <string>
#include "SDL.h"
#include "Image.h"
#include "GameState.h"
#include "ListaT.h"
#include "Vector2.h"
#include <math.h>

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
	void DrawTriangle(float x, float y, float h, float b, Vector2 direction);
	void DrawTriangle(float x, float y, float h, float b);
	void DrawTriangle(float x, float y, float h, float b, int R, int B, int G);
	void DrawCircle(float x, float y, float r, int R, int B, int G);
	void DrawVector(float x, float y, float v1, float v2, int R, int G, int B);
private:
	void RenderTexture(Image* image, int x, int y, double a);

};