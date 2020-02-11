#pragma once
#include "GameState.h"
#include "Text.h"
#include "Agent.h"
#include "Wall.h"
#include "Image.h"

class ArriveScreen : public GameState
{
private:
	Platform* platform;
	GameStateManager* manager;
	Agent agent1;
public:
	ArriveScreen();
	~ArriveScreen();
	void Init(Platform* platform, GameStateManager* manager) override;
	void Draw() override;
	bool Input(ListaT<int>* keyDowns, ListaT<int>* keyUps, bool* leftclick, float* mouseX, float* mouseY) override;
	void Update() override;
	void Close() override;
};

