#include "Vector2.h"

Vector2::Vector2()
{
	_x = 0;
	_y = 0;
}

Vector2::Vector2(float x, float y)
{
	_x = x;
	_y = y;
}

void Vector2::SetValue(float x, float y)
{
	_x = x;
	_y = y;
}

float Vector2::GetX()
{
	return _x;
}

float Vector2::GetY()
{
	return _y;
}
