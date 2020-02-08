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
	void SetValue(Vector2 vec);
	float GetX();
	float GetY();
	void Normalize();
	void Scale(float S);
	void Scale(float s1, float s2);
};

