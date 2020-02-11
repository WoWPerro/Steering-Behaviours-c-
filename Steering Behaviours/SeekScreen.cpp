#include "SeekScreen.h"

SeekScreen::SeekScreen()
{

}

SeekScreen::~SeekScreen()
{

}

void SeekScreen::Init(Platform* platform, GameStateManager* manager)
{
	this->platform = platform;
	this->manager = manager;
	agent1.SetPos(platform->width / 2, platform->height / 2);
	std::cout << " Game Init" << std::endl;
	agent1.SetType(type::Seek);
	agent1.SetMaxSpeed(15);
	agent1.SetMaxSteer(1);
}

void SeekScreen::Draw()
{
	platform->RenderClear();
	std::cout << " Game Draw" << std::endl;
	platform->DrawTriangle(agent1.GetPos().GetX(), agent1.GetPos().GetY(), 60, 40, agent1.GetVel());
	platform->DrawVector(agent1.GetPos().GetX(), agent1.GetPos().GetY(), agent1.GetPos().GetX() + agent1.GetVel().GetX() * 5, agent1.GetPos().GetY() + agent1.GetVel().GetY() * 5, 0xff, 0xa4, 0x40);
	platform->RenderPresent();
}

bool SeekScreen::Input(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool* leftclick, float* mouseX, float* mouseY)
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

void SeekScreen::Update()
{
	agent1.UpdateAgent();
	std::cout << " Game Update" << std::endl;
}

void SeekScreen::Close()
{
	std::cout << " Close Init" << std::endl;
}