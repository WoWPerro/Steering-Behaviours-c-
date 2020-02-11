#pragma once
class Wall
{
private:
	float _radius;
	float _x;
	float _y;
public:
	Wall();
	Wall(float x, float y, float radius);
	float GetX();
	float GetY();
	float GetR();
	void SetX(float x);
	void SetY(float y);
	void SetR(float r);
};

