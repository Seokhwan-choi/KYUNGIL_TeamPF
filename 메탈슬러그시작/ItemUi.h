#pragma once
#include "GameObject.h"
class ItemUi : public GameObject
{
public:
	ItemUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~ItemUi();
};

