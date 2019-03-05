#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
#include "BubbleCrab.h"

//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	_player = new Player("플레이어", { 100, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	//잠자리 생성
	//FlyBug* _flyBug = new FlyBug("flyBug", { WINSIZEX / 2 + 300, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug);

	//게 생성
<<<<<<< HEAD
	//Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//게 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab);

	//거품게 생성
	BubbleCrab* _bubbleCrab = new BubbleCrab("bubbleCrab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//거품게 객체 추가하기
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab);
=======
	Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175 }, { 150, 150 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab);
>>>>>>> bff7872a103319ba10b81591a195928eddbabd18

	OBJECTMANAGER->Init();

	return S_OK;	
	//return S_OK밑에 코드 있으면 안됨!!!!!!!!!!!
}

//==========================================================================//
//						## 해제 ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();
	//이미지 클래스를 날갈떄까진 사용할 일 없다.
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE();		
	

}

//==========================================================================//
//						## 업데이트 ## update(void)							//
//==========================================================================//
void MainGame::update(void)
{
	gameNode::update();

	OBJECTMANAGER->Update();
	
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
	OBJECTMANAGER->Render();

	
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());

}