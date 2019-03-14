#include "stdafx.h"
#include "GameOverUi_2.h"




GameOverUi_2::GameOverUi_2(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_gameOverImage = IMAGEMANAGER->findImage("gameover");
	//========================================================
	//이미지 변수 int형 선언
	//========================================================
	_count = 0;
	_index = 0;
	//바탕
	backgroundRc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	//불변수 선언
	_isShow = false;

}

GameOverUi_2::~GameOverUi_2()
{
}

HRESULT GameOverUi_2::Init()
{
	return S_OK;
}

void GameOverUi_2::Release()
{
}

void GameOverUi_2::Update()
{
}

void GameOverUi_2::Render()
{
	if (_isShow == true) {
		_gameOverImage->frameRender(getMemDC(), backgroundRc.left, backgroundRc.top);
	}
}

void GameOverUi_2::gameOver()
{
	_count++;
	_gameOverImage->setFrameY(0);
	if (_count % 100 == 0) {
		_index++;
		if (_index > 1) {
			_index = 1;
		}
		_gameOverImage->setFrameX(_index);
	}
	if (_count == 300) {
		SCENEMANAGER->ChangeScene("시작화면");
	}


}
