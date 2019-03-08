#include "stdafx.h"
#include "stage1Scene.h"
#include "GameOverUi.h"
#include "stage1StartUi.h"
#include "timeUi.h"
#include "GameOverUi_2.h"
HRESULT stage1Scene::Init(void)
{
	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);
	
	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);

	stage1StartUi* _stage1startui = new stage1StartUi("stage1startui", { 0,0 }, {0,0}, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _stage1startui);

	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);

	return S_OK;
}

void stage1Scene::Release(void)
{
	OBJECTMANAGER->Release();
}

void stage1Scene::Update(void)
{
	OBJECTMANAGER->Update();
}

void stage1Scene::Render(void)
{
	OBJECTMANAGER->Render();
}
