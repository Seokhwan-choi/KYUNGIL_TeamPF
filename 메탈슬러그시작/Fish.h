#pragma once
#include "GameObject.h"
class Fish : public GameObject
{
private:
	STATE _state;

public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();
};

