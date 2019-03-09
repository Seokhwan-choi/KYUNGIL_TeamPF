#include "stdafx.h"
#include "timeUi.h"
#include "GameOverUi.h"
timeUi::timeUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	// 시간 관련 변수 초기화
	//========================================================
	_time = 60;
	_count = 0;

	//이미지 초기화
	_timeImg = IMAGEMANAGER->addFrameImage("제한시간", "UI/timenumber.bmp", 510, 69, 10.1, true, RGB(255, 0, 255));
	//불변수 초기화
	_isShow = true;
}

timeUi::~timeUi()
{
}

HRESULT timeUi::Init()
{

	return S_OK;
}

void timeUi::Release()
{
}

void timeUi::Update()
{
	//4초마다 1씩 감소하도록 한다
	_count++;
	if (_count % 400 == 0) {
		_time--;
	}
	if (_time <= 0) {
		_time = 0;
	}
	
	if (_time <= 0) {
		//캐릭터 종료씬update부분 넣어준다.
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->setIsShow(true);
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->gameOver();
	}

}

void timeUi::Render()
{
	if (_isShow == true) {
		if (_time < 10) _timeImg->frameRender(getMemDC(), 569, 33, _time, 0);
		if (_time >= 10) {
			_timeImg->frameRender(getMemDC(), 569, 33, (_time - _time % 10) / 10, 0);
			_timeImg->frameRender(getMemDC(), 620, 33, _time % 10, 0);
		}
	}
}
