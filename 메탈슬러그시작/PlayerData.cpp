as#include "stdafx.h"
#include "PlayerData.h"


PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}

HRESULT PlayerData::Init()
{
	_arms = 0;
	_life = 2;
	_bomb = 10;
	_score = 0;
	_saveCaptive = 4;
	_weapon = WEAPON::NORMAL;
	



	return S_OK;
}
//������ �ٽ� ��Ƴ���~
void PlayerData::CheckPoint()
{
	if (SCENEMANAGER->FindScene("������������")) {
		_savePt = { WINSIZEX - 150, WINSIZEY / 2 };
	}
	else {
		_savePt = { WINSIZEX / 2, WINSIZEY / 5 };
	}
}
