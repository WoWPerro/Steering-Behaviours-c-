#include "Agent.h"

Agent::Agent()
{

}

Agent::Agent(type type)
{
	_type = type;
}

void Agent::SetType(type t)
{
	_type = t;
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

void Agent::SetMaxSpeed(float m)
{
	_maxSpeed = m;
}

void Agent::SetMaxSteer(float s)
{
	_maxSteer = s;
}

void Agent::UpdateAgent()
{
	switch(_type)
	{
		case type::Arrive:
		{
			
		}
			
		break;

		case type::Evade:

		break;

		case type::Flee:

		break;

		case type::Hide:

		break;

		case type::Interpose:

		break;

		case type::ObstacleAvoidance:

		break;

		case type::OffsetPursuit:

		break;

		case type::PathFolliwing:

		break;

		case type::Pursuit:

		break;

		case type::Seek:
		{
			Vector2 desiredVel;
			desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); //resta de posiciones para sacar vector
			desiredVel.Normalize();
			desiredVel.Scale(_maxSpeed);
			Vector2 steeringforce;
			steeringforce.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
			steeringforce.Normalize();
			steeringforce.Scale(_maxSteer);
			Vector2 NewVel;
			NewVel.SetValue(_vel.GetX() + steeringforce.GetX(), _vel.GetY() + steeringforce.GetY());
			NewVel.Normalize();
			NewVel.Scale(_maxSpeed);
			_vel.SetValue(NewVel);
			_position.SetValue(_position.GetX() + _vel.GetX(),_position.GetY() + _vel.GetY());
			_rotation = _vel;
		}
		break;

		case type::WallAvoidance:

		break;

		case type::Wander:

		break;
	}
}