#pragma once
#include "gameNode.h"

class MainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame() {}
	~MainGame() {}
};