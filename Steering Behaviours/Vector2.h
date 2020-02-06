#pragma once
class Vector2
{
private:
	float _x;
	float _y;
public:
	Vector2();
	Vector2(float x, float y);
	void SetValue(float x, float y);
	float GetX();
	float GetY();
};

