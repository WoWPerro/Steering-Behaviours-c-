#include "Game.h"
#include<iostream>
#include <sstream> 

ListaT<int> extractIntegerWords(std::string str)
{
	ListaT<int> Results;
	std::stringstream ss;

	/* Storing the whole string into string stream */
	ss << str;

	/* Running loop till the end of the stream */
	std::string temp;
	int found;
	while (!ss.eof())
	{

		/* extracting word by word from stream */
		ss >> temp;

		/* Checking the given word is integer or not */
		if (std::stringstream(temp) >> found)
			Results.push_back(found);
	}
	return Results;
}

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(Platform* platform, GameStateManager* manager)
{
	this->platform = platform;
	this->manager = manager;
	agent1.SetPos(platform->width/2, platform->height / 2);
	std::cout << " Game Init" << std::endl;
}

void Game::Draw()
{
	platform->RenderClear();
	std::cout << " Game Draw" << std::endl;
	platform->DrawTriangle(agent1.GetPos().GetX(), agent1.GetPos().GetY(), 60, 40);
	platform->RenderPresent();
}

bool Game::Input(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool* leftclick, float* mouseX, float* mouseY)
{
	if (!(keyUps->size == 0))
	{
		for (int i = 0; i < keyUps->size; i++)
		{
			int num = keyUps->get_at(i)->value;
			if (num == 27)
			{
				exit(1);
			}
		}
	}

	if (!(keyDowns->size == 0))
	{
		for (int i = 0; i < keyDowns->size; i++)
		{
			int num = keyDowns->get_at(i)->value;
		}
	}

	std::cout << " Game Input" << std::endl;
	return false;
}

void Game::Update()
{
	std::cout << " Game Update" << std::endl;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}