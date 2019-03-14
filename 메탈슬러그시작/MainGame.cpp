#include "stdafx.h"
#include "MainGame.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "startScene.h"
#include "choiceScene.h"
#include "BaseMent.h"
#include "BossStage.h"
#include "LoadingScene.h"

//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 
	
	SCENEMANAGER->AddScene("시작화면", new startScene);
	SCENEMANAGER->AddScene("캐릭터선택화면", new choiceScene);
	SCENEMANAGER->AddScene("스테이지원", new StageOne);
	SCENEMANAGER->AddScene("지하스테이지", new BaseMent);
	SCENEMANAGER->AddScene("보스스테이지", new BossStage);
	SCENEMANAGER->AddScene("로딩", new LoadingScene);
	//첫 시작화면
	SCENEMANAGER->ChangeScene("스테이지원");
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