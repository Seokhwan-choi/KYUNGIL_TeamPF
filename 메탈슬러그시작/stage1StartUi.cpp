#include "stdafx.h"
#include "stage1StartUi.h"



//mission1 start! 
stage1StartUi::stage1StartUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	//이미지 렉트 
	//========================================================

	_y = { 256,462 }; //위 y 아래 y 
	_wh = { 79,109 };
	//위렉트 위치 좌표
	_site[0] = { 349,_y.x };			_site[1] = { 428, _y.x };			_site[2] = { 472, _y.x };
	_site[3] = { 550,_y.x };			_site[4] = { 630, _y.x };			_site[5] = { 676, _y.x };
	_site[6] = { 754,_y.x };			_site[7] = { 893, _y.x };			
	//아래렉트 위치 좌표
	_site[8] = { 412,_y.y };			_site[9] = { 495, _y.y };			_site[10] = { 565, _y.y };
	_site[11] = { 640,_y.y };			_site[12] = { 714, _y.y };			_site[13] = { 789, _y.y };

	for (int i = 0; i < 14; i++) {
		startRc[i] = RectMake(_site[i].x, _site[i].y, _wh.x, _wh.y);
	}
	
	//이미지 
	for (int i = 0; i < 14; i++) {
		string num = to_string(i+1);
		string temp = "UI/stage1StartScene/number";
		string end = ".bmp";
		string name = temp + num;
		string fullName = name + end;
		_textImg[i] = IMAGEMANAGER->addImage(name, fullName.c_str(),_site[i].x,_site[i].y, _wh.x, _wh.y, true, RGB(255,0,255));
	}
	//움직임을 위한 변수
	_angle = PI * 3/ 4;
	_speed = 14.4f;
	_count = 0;
	_isMove = false;
		
}

stage1StartUi::~stage1StartUi()
{
}

HRESULT stage1StartUi::Init()
{
	
	return S_OK;
}

void stage1StartUi::Release()
{
}

void stage1StartUi::Update()
{
	_count++;
	if (_count == 130)
	{
		_isMove = true;
	}
	if (_isMove == true) {
		for (int i = 0; i < 8; i++) {
			_site[i].x += cosf(_angle - (PI/12* i))*_speed;
			_site[i].y -= sinf(_angle - (PI/12 * i))*_speed;
		}
		for (int i = 8; i < 14; i++) {
			_site[i].x += cosf(PI +  (PI/6* (i - 8 )))* _speed;
			_site[i].y -= sinf(PI + (PI / 6* (i - 8 )))* _speed;
		}
	}
	for (int i = 0; i < 14; i++) {
		startRc[i] = RectMake(_site[i].x, _site[i].y, _wh.x, _wh.y);
	}

}

void stage1StartUi::Render()
{
	//렉트 보여줄 토글키
	if(KEYMANAGER->isToggleKey('A')) {
		for (int i = 0; i < 14; i++) {
			Rectangle(getMemDC(), startRc[i]);
		}
	}
	//이미지
	if ((_count > 80 && _count < 95) ||( _count > 110 && _count < 125)) {
		for (int i = 0; i < 14; i++) {
			_textImg[i]->alphaRender(getMemDC(), startRc[i].left, startRc[i].top, 0);
		}
	}
	else {
		for (int i = 0; i < 14; i++) {
		_textImg[i]->render(getMemDC(), startRc[i].left, startRc[i].top);
		}
	}
}
