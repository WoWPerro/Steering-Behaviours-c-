#include "Vector2.h"
#include <math.h>

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

void Vector2::SetValue(Vector2 vec)
{
	_x = vec.GetX();
	_y = vec.GetY();
}

float Vector2::GetX()
{
	return _x;
}

float Vector2::GetY()
{
	return _y;
}

void Vector2::Normalize()
{
	float x1 = _x * _x;
	float y1 = _y * _y;
	float magnitude = pow(x1 + y1, 0.5);
	_x = _x / magnitude;
	_y = _y / magnitude;
}

void Vector2::Scale(float s)
{
	_x = _x * s;
	_y = _y * s;
}

void Vector2::Scale(float s1, float s2)
{
	_x = _x * s1;
	_y = _y * s2;
}