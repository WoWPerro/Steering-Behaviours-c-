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
	float magnitude = powf(x1 + y1, 0.5f);
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

int Vector2::distance(Vector2 v1, Vector2 v2)
{
	float r1;
	r1 = (powf(v2.GetX() - v1.GetX(), 2) + powf(v2.GetY() - v1.GetY(), 2));
	float distance = powf(r1, 0.5f);
	return distance;
}

int Vector2::length()
{
	float r1;
	r1 = (powf(_x, 2) + powf(_y, 2));
	float length = powf(r1, 0.5f);
	return length;
}
