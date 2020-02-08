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
	Vector2 _rotation;
	float _maxSpeed;
	float _maxSteer;
	type _type = type::Default;
public:
	Agent();
	Agent(type type);
	void UpdateAgent();
	void SetPos(float x, float y);
	void SetVel(float x, float y);
	void SetTarget(float x, float y);
	void SetMaxSpeed(float m);
	void SetMaxSteer(float s);
	void SetType(type t);
	Vector2 GetPos();
	Vector2 GetVel();
	Vector2 GetTarget();
	Vector2 GetRotation();
};