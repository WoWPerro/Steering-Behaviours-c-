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
	Wall wall(1500,500,150);
	walls.push_back(wall);
	agent1.SetWalls(walls);
	std::cout << " Game Init" << std::endl;
	agent1.SetType(type::Seek);
	agent1.SetMaxSpeed(30);
	agent1.SetMaxSteer(1);
	//===========================================
	//agent1.SetType(type::Arrive);
	//agent1.SetMaxSpeed(4);
	//agent1.SetMaxSteer(20);
	//agent1.SetSlowingRadius(800);
	//===========================================
	//agent1.SetType(type::Flee);
	//agent1.SetMaxSpeed(20);
	//agent1.SetMaxSteer(20);
	//agent1.SetSlowingRadius(300);
	//=========================================
	/*agent1.SetType(type::Wander);
	agent1.SetMaxSpeed(20);
	agent1.SetMaxSteer(20);
	agent1.SetSlowingRadius(800);*/
	//==========================================
	//agent1.SetType(type::ObstacleAvoidance);
	//agent1.SetMaxSpeed(8);
	//agent1.SetMaxSteer(20);
}

void Game::Draw()
{
	platform->RenderClear();
	std::cout << " Game Draw" << std::endl;
	platform->DrawTriangle(agent1.GetPos().GetX(), agent1.GetPos().GetY(), 60, 40, agent1.GetVel());

	for (int i = 0; i < walls.size; i++)
	{
		float wx = walls.get_at(i)->value.GetX();
		float wy = walls.get_at(i)->value.GetY();
		float wr = walls.get_at(i)->value.GetR();
		platform->DrawCircle(wx, -wy, wr, 0xFF, 0x00, 0x40);;
	}
	platform->DrawCircle(agent1.GetTarget().GetX(), -agent1.GetTarget().GetY(), agent1.GetSlowingRadius(), 0x40, 0xff, 0x00);
	platform->DrawVector(agent1.GetPos().GetX(), agent1.GetPos().GetY(), agent1.GetPos().GetX() + agent1.GetVel().GetX() * 5, agent1.GetPos().GetY() + agent1.GetVel().GetY()* 5, 0xff, 0xa4, 0x40);
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


	agent1.SetTarget(*mouseX, *mouseY);
	std::cout << " Game Input" << std::endl;
	return false;
}

void Game::Update()
{
	agent1.UpdateAgent();
	std::cout << " Game Update" << std::endl;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}