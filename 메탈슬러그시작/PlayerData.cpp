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
	_arms = 0;
	_life = 2;
	_bomb = 10;
	_score = 0;
	_saveCaptive = 4;
	_weapon = WEAPON::NORMAL;
	//if()


	return S_OK;
}
