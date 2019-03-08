#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
#include "BubbleCrab.h"
#include "Fish.h"
#include "BigCrab.h"


//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	SCENEMANAGER->AddScene("스테이지 원", new StageOne);
	SCENEMANAGER->ChangeScene("스테이지 원");

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	//잠자리 생성
	//FlyBug* _flyBug = new FlyBug("flyBug", { WINSIZEX / 2 + 300, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug);

	//게 생성
	//Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175}, { 100, 150 }, GameObject::Pivot::Center);
	//게 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab);

	//거품게 생성
	//BubbleCrab* _bubbleCrab = new BubbleCrab("bubbleCrab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//거품게 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab);

	//물고기 생성
	//Fish* fish = new Fish("fish", { WINSIZEX / 2 + 200,WINSIZEY / 2 + 200}, { 100,100 }, GameObject::Pivot::Center);
	//물고기 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, fish);

	//큰게 생성
	BigCrab* bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110}, { 200,280 }, GameObject::Pivot::Center);
	//큰게 객체 추가하기
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, bigCrab);


	OBJECTMANAGER->Init();

	return S_OK;	
}

//==========================================================================//
//						## 해제 ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->Release();
}

//==========================================================================//
//						## 업데이트 ## update(void)							//
//==========================================================================//
void MainGame::update(void)
{
	gameNode::update();	
	SCENEMANAGER->Update();
}

//==========================================================================//
//						## 렌더 ## render(HDC hdc)							//
//==========================================================================//
void MainGame::render()
{		
	//벡버퍼 가져오기 (이건 렌더에 그냥두기)
	HDC memDC = this->getBackBuffer()->getMemDC();

	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================================//
	SCENEMANAGER->Render();
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());

}