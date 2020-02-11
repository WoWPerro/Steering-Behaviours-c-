#include "Agent.h"
#include <random>

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

float Agent::GetSlowingRadius()
{
	return _slowingRadius;
}

void Agent::SetMaxSpeed(float m)
{
	_maxSpeed = m;
}

void Agent::SetMaxSteer(float s)
{
	_maxSteer = s;
}

void Agent::SetSlowingRadius(float s)
{
	_slowingRadius = s;
}

void Agent::SetWalls(ListaT<Wall> w)
{
	wallList = w;
}

Vector2 Agent::GetSteering()
{
	return _steering;
}

void Agent::UpdateAgent()
{
	switch(_type)
	{
		case type::Arrive:
		{
			Vector2 desiredVel;
			desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); 
			desiredVel.Normalize();
			desiredVel.Scale(_maxSpeed);
			_steering.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
			_steering.Normalize();
			_steering.Scale(_maxSteer);
			float distance;
			distance = desiredVel.distance(_target, _position);
			if (distance > _slowingRadius)
			{
				Vector2 NewVel;
				NewVel.SetValue(_vel.GetX() + _steering.GetX(), _vel.GetY() + _steering.GetY());
				NewVel.Normalize();
				NewVel.Scale(_maxSpeed);
				_vel.SetValue(NewVel);
				_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
				_rotation = _vel;
			}
			else
			{
				Vector2 NewVel;
				NewVel.SetValue(desiredVel.GetX() * _maxSpeed/10 * (distance/_slowingRadius), desiredVel.GetY() * _maxSpeed/10 * (distance / _slowingRadius));
				_vel.SetValue(NewVel);
				_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
				_rotation = _vel;
			}
		}
			
		break;

		case type::Evade:

		break;

		case type::Flee:
		{
			Vector2 desiredVel;
			desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY());
			desiredVel.Normalize();
			_steering.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
			_steering.Normalize();
			_steering.Scale(_maxSteer);
			//Vector2 fleeDesiredVel;
			//fleeDesiredVel.SetValue(-desiredVel.GetX(), -desiredVel.GetY()); //Aquí es donde lo vuelves negativo para que huya
			Vector2 NewVel;
			NewVel.SetValue(_vel.GetX() + _steering.GetX(), _vel.GetY() + _steering.GetY());
			NewVel.Normalize();
			NewVel.Scale(_maxSpeed);
			_vel.SetValue(NewVel);
			_position.SetValue(_position.GetX() - _vel.GetX(), _position.GetY() - _vel.GetY()); //Aquí es donde lo vuelves negativo para que huya
			_rotation = _vel;
		}			
		break;

		case type::Hide:

		break;

		case type::Interpose:

		break;

		case type::ObstacleAvoidance:
		{
			Vector2 desiredVel;
			desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); //resta de posiciones para sacar vector
			desiredVel.Normalize();
			desiredVel.Scale(_maxSpeed);
			_steering.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
			_steering.Normalize();
			_steering.Scale(_maxSteer);
			float maxSeeahead = 100;
			float Max_Avoid_Force = 100;
			Vector2 ahead;
			ahead.SetValue(_position.GetX() + _vel.GetX() * maxSeeahead, _position.GetY() + _vel.GetY() * maxSeeahead);
			Vector2 ahead2;
			ahead2.SetValue(_position.GetX() + _vel.GetX() * (maxSeeahead / 2), _position.GetY() + _vel.GetY() * (maxSeeahead / 2));
			float wall = -1;
			float closer = 100000000;
			Vector2 CirclePos;
			for (int i = 0; i < wallList.size; i++)
			{
				CirclePos.SetValue(wallList.get_at(i)->value.GetX(), wallList.get_at(i)->value.GetY());
				float distance = ahead.distance(ahead2, CirclePos);
				if (distance <= wallList.get_at(i)->value.GetR())
				{
					if (distance < closer)
					{
						closer = distance;
						wall = i;
					}
				}
			}
			Vector2 avoidance;
			if (wall != -1)
			{
				avoidance.SetValue(ahead.GetX() - CirclePos.GetX(), ahead.GetY() - CirclePos.GetY());
				avoidance.Normalize();
				avoidance.Scale(Max_Avoid_Force);
			}
			Vector2 NewVel;
			NewVel.SetValue(_vel.GetX() + _steering.GetX() - avoidance.GetX(), _vel.GetY() + _steering.GetY() - avoidance.GetY());
			NewVel.Normalize();
			NewVel.Scale(_maxSpeed);
			_vel.SetValue(NewVel);
			_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
			_rotation = _vel;
		}
		break;

		case type::OffsetPursuit:

		break;

		case type::PathFolliwing:

		break;

		case type::Pursuit:
		{
			float futureVision;
			Vector2 desiredVel;
			desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); //resta de posiciones para sacar vector
			desiredVel.Normalize();
			desiredVel.Scale(_maxSpeed);
			_steering.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
			_steering.Normalize();
			_steering.Scale(_maxSteer);
			Vector2 NewVel;
			NewVel.SetValue(_vel.GetX() + _steering.GetX(), _vel.GetY() + _steering.GetY());
			NewVel.Normalize();
			NewVel.Scale(_maxSpeed);
			_vel.SetValue(NewVel);
			_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
			_rotation = _vel;
		}		
		break;

		case type::Seek:
		{
				Vector2 desiredVel;
				desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); //resta de posiciones para sacar vector
				desiredVel.Normalize();
				desiredVel.Scale(_maxSpeed);
				_steering.SetValue(desiredVel.GetX() - _vel.GetX(), desiredVel.GetY() - _vel.GetY());
				_steering.Normalize();
				_steering.Scale(_maxSteer);
				Vector2 NewVel;
				NewVel.SetValue(_vel.GetX() + _steering.GetX(), _vel.GetY() + _steering.GetY());
				NewVel.Normalize();
				NewVel.Scale(_maxSpeed);
				_vel.SetValue(NewVel);
				_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
				_rotation = _vel;
		}
		break;

		case type::WallAvoidance:
		{
			
			
		}			
		break;

		case type::Wander:
		{
			float circleDistance = 50; //Hacer RANDOMMMMMMMMMMM
			float circleRadius = 50; //Hacer RANDOMMMMMMMMMMM
			float ANGLE_CHANGE = 20;
			Vector2 CircleCenter;
			CircleCenter.SetValue(_vel);
			CircleCenter.Normalize();
			Vector2 Displacement(0, -1);
			Displacement.Scale(circleRadius);
			CircleCenter.Scale(circleDistance);
			//SetAngle
			Vector2 NewVel2;
			NewVel2.SetValue(_vel.GetX(), _vel.GetY());
			NewVel2.Normalize();
			NewVel2.Scale(_maxSpeed);
			_vel.SetValue(NewVel2);
			float angleX = cos(NewVel2.GetX()) * Displacement.length();
			float angleY = sin(NewVel2.GetY()) * Displacement.length();
			float wanderAngle;
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(1.0, 40.0);
			wanderAngle = dist(mt) * ANGLE_CHANGE - ANGLE_CHANGE * .5;
			CircleCenter.SetValue(CircleCenter.GetX() + Displacement.GetX(), CircleCenter.GetY() - Displacement.GetY());
			_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
			//Vector2 desiredVel;
			//desiredVel.SetValue(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY()); //resta de posiciones para sacar vector
			//desiredVel.Normalize();
			//desiredVel.Scale(_maxSpeed);
			_steering.SetValue(Displacement.GetX()+ angleX, Displacement.GetY() - angleY);
			_steering.Normalize();
			_steering.Scale(_maxSteer);
			Vector2 NewVel;
			NewVel.SetValue(_vel.GetX() + _steering.GetX(), _vel.GetY() + _steering.GetY());
			NewVel.Normalize();
			NewVel.Scale(_maxSpeed);
			_vel.SetValue(NewVel2);
			_position.SetValue(_position.GetX() + _vel.GetX(), _position.GetY() + _vel.GetY());
			_rotation = _vel;
		}
		break;
	}
	if (_position.GetX() > 1920 || _position.GetY() > 1080)
	{
		_position.SetValue(500, 500);
	}
	else if (_position.GetX() < 0 || _position.GetY() < 0)
	{
		_position.SetValue(500, 500);
	}
}