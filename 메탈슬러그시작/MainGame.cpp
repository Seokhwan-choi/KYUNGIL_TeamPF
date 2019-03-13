#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "startScene.h"
#include "choiceScene.h"
#include "stage1Scene.h"
#include "BaseMent.h"
#include "BossStage.h"
#include "LoadingScene.h"
//==========================================================================//
//						## 초기화 ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	startScene* _startscene = new startScene;
	choiceScene* _choicescene = new choiceScene;
	stage1Scene* _stage1 = new stage1Scene;
	SCENEMANAGER->AddScene("시작화면", _startscene);
	SCENEMANAGER->AddScene("캐릭터선택화면", _choicescene);
	SCENEMANAGER->AddScene("스테이지 원", new StageOne);
	SCENEMANAGER->AddScene("스테이지1", _stage1);
	SCENEMANAGER->AddScene("지하스테이지", new BaseMent);
	SCENEMANAGER->AddScene("보스스테이지", new BossStage);
	SCENEMANAGER->AddScene("로딩", new LoadingScene);
	//첫 시작화면
	SCENEMANAGER->ChangeScene("로딩");

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