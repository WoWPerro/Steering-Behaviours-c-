#include "Agent.h"

Agent::Agent()
{

}

Agent::Agent(type type)
{
	_type = type;
}

void Agent::SetPos(float x, float y)
{
	_position.SetValue(x, y);
}

void Agent::SetVel(float x, float y)
{
	_vel.SetValue(x, y);
}

void Agent::SetTarget(float x, float y)
{
	_target.SetValue(x, y);
}

Vector2 Agent::GetPos()
{
	return _position;
}

Vector2 Agent::GetVel()
{
	return _vel;
}

Vector2 Agent::GetTarget()
{
	return _target;
}