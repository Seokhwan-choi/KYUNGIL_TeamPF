#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"

HRESULT StageOne::Init()
{
	// StageOne���� ����� ������Ʈ �������ش�.
	Player* _player = new Player("player", { WINSIZEX / 2, WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _player);

	OBJECTMANAGER->Init();
	return S_OK;
}

void StageOne::Release()
{
	OBJECTMANAGER->Release();
}

void StageOne::Update()
{
	OBJECTMANAGER->Update();
}

void StageOne::Render()
{
	OBJECTMANAGER->Render();
}
