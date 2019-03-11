#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
#include "BubbleCrab.h"
#include "Fish.h"
#include "BigCrab.h"
#include "Boss.h"
#include "startScene.h"
#include "choiceScene.h"
#include "stage1Scene.h"

//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	SCENEMANAGER->AddScene("스테이지 원", new StageOne);
	SCENEMANAGER->ChangeScene("스테이지 원");


	_player = new Player("플레이어", { WINSIZEX - 200, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);


	//보스 생성
	_boss = new Boss("boss", { -WINSIZEX / 4, WINSIZEY / 2 + 100 }, { WINSIZEX / 2, WINSIZEY }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _boss);

	//OBJECTMANAGER->Init();
	//_monster = new Monster("몬스터", { WINSIZEX / 2 + 200,WINSIZEY / 2 }, { 100,100 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _monster);

	startScene* _startscene = new startScene;
	SCENEMANAGER->AddScene("시작화면", _startscene);
	SCENEMANAGER->ChangeScene("시작화면");

	choiceScene* _choicescene = new choiceScene;
	SCENEMANAGER->AddScene("캐릭터선택화면", _choicescene);

	//첫 시작화면
	//stage1Scene* _stage1 = new stage1Scene;
	//SCENEMANAGER->AddScene("스테이지1", _stage1);

	/*
	undergroundScene* _underground = new undergroundScene;
	SCENEMANAGER->AddScene("스테이지1_1", _underground);
	underriverScene&  _underriver = new underriverScene;
	SCENEMANAGER->AddScene("스테이지1_2", _underriver);
	boosScene&  _bossscene = new boosScene;
	SCENEMANAGER->AddScene("스테이지1_2", _bossscene);
	*/

	SCENEMANAGER->Init();
	return S_OK;	
}

//==========================================================================//
//						## 해제 ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->Release();

	//이미지 클래스를 날갈떄까진 사용할 일 없다.
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE();		
}

//==========================================================================//
//						## 업데이트 ## update(void)							//
//==========================================================================//
void MainGame::update(void)
{
	gameNode::update();	
	SCENEMANAGER->Update();
	//OBJECTMANAGER->Update();
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
	//OBJECTMANAGER->Render();

	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());

}