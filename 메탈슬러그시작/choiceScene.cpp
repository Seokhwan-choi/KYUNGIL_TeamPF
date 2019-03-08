#include "stdafx.h"
#include "choiceScene.h"
#include "choiceUi.h"

HRESULT choiceScene::Init(void)
{
	choiceUi* _choiceui = new choiceUi("choiceui", { 0,0 }, {0,0}, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _choiceui);
	return S_OK;
}

void choiceScene::Release(void)
{
	OBJECTMANAGER->Release();
}

void choiceScene::Update(void)
{
	OBJECTMANAGER->Update();
}

void choiceScene::Render(void)
{
	OBJECTMANAGER->Render();
}
