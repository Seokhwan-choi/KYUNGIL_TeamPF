#include "stdafx.h"
#include "StageTwo.h"
#include "Rect.h"
#include "realPlayer.h"
#include "oldMan.h"
#include "Item.h"

HRESULT StageTwo::Init()
{
	Rect* _rect = new Rect("rect", { WINSIZEX / 2, WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _rect);

	realPlayer* _realplayer = new realPlayer("realplayer", { (WINSIZEX / 4) * 2, WINSIZEY / 2 }, { 10,10 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _realplayer);

	//위치값만 바꿔주도록하여 생성하도록 한다
	for (int i = 0; i < 3; i++)
	{
		oldMan* _oldman = new oldMan("oldman", {(float) (WINSIZEX / 4) * 3 + 30*i, (float)WINSIZEY / 2 }, { 100,100 }, GameObject::Pivot::LeftTop);
		OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _oldman);
		//아이템 
		Item * _item = new Item("item", { (float)(_oldman->GetRect().left), (float)(_oldman->GetRect().top) }, { 20,20 }, GameObject::Pivot::LeftTop);
		OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _item);
	}

	
	
	OBJECTMANAGER->Init();

	return S_OK;
}

void StageTwo::Release()
{
	OBJECTMANAGER->Release();

}

void StageTwo::Update()
{
	OBJECTMANAGER->Update();
}

void StageTwo::Render()
{
	OBJECTMANAGER->Render();
}
