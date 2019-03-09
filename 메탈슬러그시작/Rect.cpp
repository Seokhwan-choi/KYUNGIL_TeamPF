#include "stdafx.h"
#include "Rect.h"

Rect::Rect(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// 클래스 이름 설정 해준다.
	_position = pos;			// 좌표 초기화 해준다.
	_size = size;				// 사이즈 초기화 해준다.
	_pivot = Pivot::LeftTop;	// 피벗 위치 잡아준다.
	//this->UpdateRectByPivot();// RECT 그려준다.
	_isActive = true;			// 활성화 되어있다. 
	_isLive = true;				// 살아 있다.
	//제한시간 표기 하기
	_timeImage = IMAGEMANAGER->addFrameImage("number", "number.bmp", 310, 34, 10, 1, true, RGB(0, 248, 0));
	_count = 0;
	_playTime = 12458;
	
}

HRESULT Rect::Init()
{
	//_timeImage = IMAGEMANAGER->addFrameImage("number", "number.bmp", 310, 34, 10, 1, true, RGB(0, 248, 0));
	//_count = 0;
	//_playTime = 128;
	return S_OK;
}

void Rect::Release()
{
}

void Rect::Update()
{
	this->UpdateRectByPivot();	// RECT 그려준다.
	_count++;
	if (_count % 100 == 0){
		_playTime--;
	}
	if (_playTime == 0){
		//종료씬넣기
		//changescene(게임오버화면)
		exit(0);
	}
}

void Rect::Render()
{
	Rectangle(getMemDC(), _rc);
	char str[128];
	sprintf(str, "플레이타임 : %d", _playTime);
	TextOut(getMemDC(), 0, 200, str, strlen(str));
	
	//숫자관련
	if (_playTime < 10)	_timeImage->frameRender(getMemDC(), 234, 100, _playTime, 0);
	if (_playTime >= 10 && _playTime< 100){
		_timeImage->frameRender(getMemDC(), 200, 100, (_playTime - _playTime % 10) / 10, 0);
		_timeImage->frameRender(getMemDC(), 234, 100, _playTime % 10, 0);
	}
	if (_playTime >= 100 && _playTime < 1000){
		_timeImage->frameRender(getMemDC(), 200, 100, (_playTime - _playTime % 100) / 100, 0);
		_timeImage->frameRender(getMemDC(), 234, 100, (_playTime / 10) % 10, 0);
		_timeImage->frameRender(getMemDC(), 268, 100, _playTime % 10, 0);
	}
	if (_playTime >= 1000 && _playTime < 10000) {
		_timeImage->frameRender(getMemDC(), 200, 100, (_playTime - _playTime % 1000) / 1000, 0);
		_timeImage->frameRender(getMemDC(), 234, 100, (_playTime % 1000) / 100, 0);
		_timeImage->frameRender(getMemDC(), 268, 100, (_playTime % 100) / 10, 0);
		_timeImage->frameRender(getMemDC(), 292, 100, _playTime % 10, 0);
	}
	if (_playTime >= 10000 && _playTime < 100000) {
		_timeImage->frameRender(getMemDC(), 200, 100, (_playTime - _playTime % 10000) / 10000, 0);
		_timeImage->frameRender(getMemDC(), 234, 100, (_playTime % 10000) / 1000, 0);
		_timeImage->frameRender(getMemDC(), 268, 100, (_playTime % 1000) / 100, 0);
		_timeImage->frameRender(getMemDC(), 292, 100, (_playTime % 100) / 10, 0);
		_timeImage->frameRender(getMemDC(), 326, 100, _playTime % 10, 0);
	}
	if (_playTime >= 100000 && _playTime < 1000000) {
		_timeImage->frameRender(getMemDC(), 200, 100, (_playTime - _playTime % 100000) / 100000, 0);
		_timeImage->frameRender(getMemDC(), 234, 100, (_playTime % 100000) / 10000, 0);
		_timeImage->frameRender(getMemDC(), 268, 100, (_playTime % 10000) / 1000, 0);
		_timeImage->frameRender(getMemDC(), 292, 100, (_playTime % 1000) / 100, 0);
		_timeImage->frameRender(getMemDC(), 326, 100, (_playTime % 100) / 10, 0);
		_timeImage->frameRender(getMemDC(), 350, 100, _playTime % 10, 0);
	}

	/*
	//1의자리
	if(변수<10){
	이미지->프레임랜더(getmemDC(), 위치, 변수,0)
	}
	//10의자리
	if(변수>=10 && 변수<100){
	변수-변수%10/10
	변수%10
	}
	//100의 자리
	if(100 ~ 999)
	{
	(변수-변수%100)/100
	(변수/10)%10
	변수%10
	}
	//1000의 자리(천)
	if(1000~9999){
	(변수-변수%1000)/1000
	(변수%1000)/100
	(변수%100)/10
	변수%10
	}
	//10000의 자리(만)
	if(10000~100000){
	(변수-변수%10000)/10000
	(변수%10000)/1000
	(변수%1000)/100
	(변수%100)/10
	변수%10
	//100000의 자리(십만)
	if(100000~100000){
	(변수-변수%100000)/100000
	(변수%100000)/10000
	(변수%10000)/1000
	(변수%1000)/100
	(변수%100)/10
	변수%10
	}
	*/
}

Rect::~Rect()
{
}
