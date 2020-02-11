#include "Wall.h"

Wall::Wall()
{
	_radius = 0;
	_x = 0;
	_y = 0;
}

Wall::Wall(float x, float y, float radius)
{
	_radius = radius;
	_x = x;
	_y = y;
}

float Wall::GetX()
{
	return _x;
}

float Wall::GetY()
{
	return _y;
}

float Wall::GetR()
{
	return _radius;
}

void Wall::SetX(float x)
{
	_x = x;
}

void Wall::SetY(float y)
{
	_y = y;
}

void Wall::SetR(float r)
{
	_radius = r;
}