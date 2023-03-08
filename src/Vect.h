#pragma once

class Vect
{
public:
	float getx();
	float gety();
	float getNorm();
	void normalize();
private:
	float x, y;
};