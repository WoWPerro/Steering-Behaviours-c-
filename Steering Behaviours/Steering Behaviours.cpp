// Steering Behaviours.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SDL.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	GameStateManager* manager = new GameStateManager();
	manager->SetState(new Game());
	manager->GameLoop();
	delete manager;
	return 0;
}