#pragma once
#include "Vector2.h"
#include "Wall.h"
#include "ListaT.h"

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
	Vector2 _steering;
	float _maxSpeed;
	float _maxSteer;
	float _slowingRadius;
	type _type = type::Default;
	ListaT<Wall> wallList;
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
	void SetSlowingRadius(float s);
	void SetWalls(ListaT<Wall> w);
	Vector2 GetPos();
	Vector2 GetVel();
	Vector2 GetTarget();
	Vector2 GetRotation();
	Vector2 GetSteering();
	float GetSlowingRadius();
};