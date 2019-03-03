#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"

//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	_player = new Player("플레이어", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _player);


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