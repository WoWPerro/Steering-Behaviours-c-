#pragma once
#include "Vector2.h"

enum class type
{
	Default,
	Seek,
	Evade,
	Flee,
	Pursuit,
	Arrive,
	Wander,
	ObstacleAvoidance,
	WallAvoidance,
	Interpose,
	Hide,
	PathFolliwing,
	OffsetPursuit,
};

class Agent
{
private:
	Vector2 _position;
	Vector2 _vel;
	Vector2 _target;
	type _type = type::Default;
public:
	Agent();
	Agent(type type);
	void SetPos(float x, float y);
	void SetVel(float x, float y);
	void SetTarget(float x, float y);
	Vector2 GetPos();
	Vector2 GetVel();
	Vector2 GetTarget();
};