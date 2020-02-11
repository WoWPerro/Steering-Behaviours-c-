#include "ArriveScreen.h"

ArriveScreen::ArriveScreen()
{

}

ArriveScreen::~ArriveScreen()
{

}

void ArriveScreen::Init(Platform* platform, GameStateManager* manager)
{
	this->platform = platform;
	this->manager = manager;
	agent1.SetPos(platform->width / 2, platform->height / 2);
	std::cout << " Game Init" << std::endl;
	agent1.SetType(type::Arrive);
	agent1.SetMaxSpeed(15);
	agent1.SetMaxSteer(1);
	agent1.SetSlowingRadius(800);
}

void ArriveScreen::Draw()
{
	platform->RenderClear();
	std::cout << " Game Draw" << std::endl;
	platform->DrawTriangle(agent1.GetPos().GetX(), agent1.GetPos().GetY(), 60, 40, agent1.GetVel());
	platform->DrawCircle(agent1.GetTarget().GetX(), -agent1.GetTarget().GetY(), agent1.GetSlowingRadius(), 0x40, 0xff, 0x00);
	platform->DrawVector(agent1.GetPos().GetX(), agent1.GetPos().GetY(), agent1.GetPos().GetX() + agent1.GetVel().GetX() * 5, agent1.GetPos().GetY() + agent1.GetVel().GetY() * 5, 0xff, 0xa4, 0x40);
	platform->RenderPresent();
}

bool ArriveScreen::Input(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool* leftclick, float* mouseX, float* mouseY)
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

void ArriveScreen::Update()
{
	agent1.UpdateAgent();
	std::cout << " Game Update" << std::endl;
}

void ArriveScreen::Close()
{
	std::cout << " Close Init" << std::endl;
}