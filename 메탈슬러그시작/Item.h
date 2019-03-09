#pragma once
#include "GameObject.h"

enum class ITEM {
	haevy,
	scoreup,
	tracer
};

class Item : public GameObject
{
private:
	ITEM _oldmanItem;
public:
	Item(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Item();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

