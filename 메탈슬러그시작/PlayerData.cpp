#include "stdafx.h"
#include "PlayerData.h"


PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}

HRESULT PlayerData::Init()
{
	//arms �� 9000�� ��� �����̴�...
	_arms = 0;
	_life = 2;
	_bomb = 10;
	_score = 0;
	_saveCaptive = 0;
	_weapon = WEAPON::HEAVY;
	


	return S_OK;
}
