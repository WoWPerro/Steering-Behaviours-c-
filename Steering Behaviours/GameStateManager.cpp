#include "GameStateManager.h"
#include <iostream>

GameStateManager::GameStateManager()
{
	platform = new Platform("Tank");
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::GameLoop()
{
	while (true)
	{
		try
		{
			if (states.size() == 0)
				throw std::exception("Error");
			auto state = states.top()->value;
			platform->CheckEvent(state, &GameState::Input);
			state->Update();
			state->Draw();

		}
		catch (...)
		{
			std::cout << "Critical error Tank is closing";
			break;
		}
	}
}

void GameStateManager::SetState(GameState* state)
{
	state->Init(platform, this);
	states.push_front(state);
}

void GameStateManager::RealaseState()
{
	auto state = states.top()->value;
	state->Close();
	states.pop();
}