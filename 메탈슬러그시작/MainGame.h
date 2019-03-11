#pragma once
#include "gameNode.h"

class MainGame : public gameNode
{
private:
	class Player* _player;
	class Monster* _monster; 
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame() {}
	~MainGame() {}
};