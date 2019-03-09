#include "stdafx.h"
#include "GameCompleteUi.h"


GameCompleteUi::GameCompleteUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	
	_y = { 256,462 };		//위 y, 아래y
	_wh = { 79,109 };		//너비 높이
	//위렉트 위치 좌표
	//위렉트 위치 좌표
	_site[0] = { 349,_y.x };			_site[1] = { 428, _y.x };			_site[2] = { 472, _y.x };
	_site[3] = { 550,_y.x };			_site[4] = { 630, _y.x };			_site[5] = { 676, _y.x };
	_site[6] = { 754,_y.x };			_site[7] = { 893, _y.x };
	//아래렉트 위치 좌표
	for (int i = 8; i < 17; i++) {
		_site[i] = { 216.f + 79.f * (i - 8) };
	}

	for (int i = 0; i < 17; i++) {
		completeRc[i] = RectMake(_site[i].x, _site[i].y, _wh.x, _wh.y);
	}

	//이미지 
	for (int i = 0; i < 17; i++) {
		string num = to_string(i + 1);
		string temp = "UI/missioncomplete/number";
		string end = ".bmp";
		string name = temp + num;
		string fullName = name + end;
		_textImg[i] = IMAGEMANAGER->addImage(name, fullName.c_str(), _site[i].x, _site[i].y, _wh.x, _wh.y, true, RGB(255, 0, 255));
	}

	//움직임
	_angle = PI + 3 / 4;
	_speed = 14.4f;
	_count = 0;
	_isMove = false;
	

}

GameCompleteUi::~GameCompleteUi()
{
}

HRESULT GameCompleteUi::Init()
{
	return S_OK;
}

void GameCompleteUi::Release()
{
}

void GameCompleteUi::Update()
{
	_count++;
	if (_count == 130) {
		_isMove = true;
	}
	if (_isMove == true) {
		for (int i = 0; i < 8; i++) {
			_site[i].x += cosf(_angle - (PI / 12 * i))*_speed;
			_site[i].y -= sinf(_angle - (PI / 12 * i))*_speed;
		}
		for (int i = 8; i < 17; i++) {
			_site[i].x += cosf(PI + (PI / 10 * (i - 8)))*_speed;
			_site[i].y -= sinf(PI + (PI / 6 * (i - 8)))*_speed;
		}
	}
	for (int i = 0; i < 17; i++) {
		completeRc[i] = RectMake(_site[i].x, _site[i].y, _wh.x, _wh.y);
	}
}

void GameCompleteUi::Render()
{
	if (KEYMANAGER->isToggleKey('A')) {
		for (int i = 0; i < 17; i++) {
			Rectangle(getMemDC(), completeRc[i]);
		}
	}
	//이미지
	//알파	
	if ((_count > 80 && _count < 95) || (_count > 110 && _count < 125)) {
		for (int i = 0; i < 17; i++) {
			_textImg[i]->alphaRender(getMemDC(), completeRc[i].left, completeRc[i].top, 0);
		}
	}
	else {
		for (int i = 0; i < 17; i++) {
			_textImg[i]->render(getMemDC(), completeRc[i].left, completeRc[i].top);
		}
	}

}
