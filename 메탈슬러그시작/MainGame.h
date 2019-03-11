#pragma once
#include "gameNode.h"

class MainGame : public gameNode
{
private:
	class Player* _player;

	class FlyBug* _flyBug;
	class Crab* _crab;
	class BubbleCrab* _bubbleCrab;
	class Fish* _fish;
	class BigCrab* _bigCrab;
	class Boss* _boss;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame() {}
	~MainGame() {}
};