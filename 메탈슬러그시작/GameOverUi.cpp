#include "stdafx.h"
#include "GameOverUi.h"
#include "GameOverUi_2.h"
#include "timeUi.h"
//========================================================
// 게임오버씬 ui( size : 1280x960 )
//========================================================
GameOverUi::GameOverUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_size = size;
	_pivot = Pivot::LeftTop;

	//========================================================
	//렉트 초기화 
	//========================================================
	//중앙 컨디뉴 및 숫자 이미지 렉트
	numberRc = RectMake(570, 444, 141, 208);
	continueRc = RectMake(400,307,435,70);
	//위쪽 컨티뉴 및 숫자 이미지 렉트
	topcontinueRc = RectMake(208, 32, 229, 71);
	topnumberRc = RectMake(440, 23, 28, 69);
	//========================================================
	//이미지 초기화 
	//========================================================
	//중앙 컨티뉴 이미지
	_continueImage = IMAGEMANAGER->addImage("continue", "UI/gameOverScene/continue.bmp", 653, 79, true, RGB(255, 0, 255));
	_numberImage = IMAGEMANAGER->addFrameImage("number", "UI/gameOverScene/gameOverNumberCenter.bmp", 2120, 234, 10, 1, true, RGB(0, 248, 0));
	_gameOverImage = IMAGEMANAGER->addFrameImage("gameover", "UI/gameOverScene/gameOverScene.bmp", 2560, 960,2,1, true, RGB(255, 0, 255));
	
	//========================================================
	//이미지 변수 int형 선언
	//========================================================
	_number = 9;
	_count = 0;
	_index = 0;
	_isShow = false;
}

GameOverUi::~GameOverUi()
{
}

HRESULT GameOverUi::Init()
{
	return S_OK;
}

void GameOverUi::Release()
{
}

void GameOverUi::Update()
{
	
}

void GameOverUi::Render()
{
	//트루일때만 보여줌
	if (_isShow == true) {
		_numberImage->frameRender(getMemDC(), numberRc.left, numberRc.top, _number, 0);
		_continueImage->render(getMemDC(), continueRc.left, continueRc.top);
		_continueImage->stretchRender(getMemDC(), topcontinueRc.left, topcontinueRc.top, 0.3f);
		_numberImage->stretchFrameRender(getMemDC(), topnumberRc.left, topnumberRc.top, _number, 0, 0.2f);
	}

}

void GameOverUi::gameOver()
{
	_count++;
	if (_count % 100 == 0) {
		_number--;
	}
	if (_number <= 0) {
		//타임 유아이 없애줌
		((timeUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "timeui"))->setIsShow(false);
		
		((GameOverUi_2*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui2"))->setIsShow(true);
		((GameOverUi_2*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui2"))->gameOver();
	}
}
