#include "stdafx.h"
#include "Rect.h"

Rect::Rect(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// Ŭ���� �̸� ���� ���ش�.
	_position = pos;			// ��ǥ �ʱ�ȭ ���ش�.
	_size = size;				// ������ �ʱ�ȭ ���ش�.
	_pivot = Pivot::LeftTop;	// �ǹ� ��ġ ����ش�.
	//this->UpdateRectByPivot();// RECT �׷��ش�.
	_isActive = true;			// Ȱ��ȭ �Ǿ��ִ�. 
	_isLive = true;				// ��� �ִ�.
	//���ѽð� ǥ�� �ϱ�
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
	this->UpdateRectByPivot();	// RECT �׷��ش�.
	_count++;
	if (_count % 100 == 0){
		_playTime--;
	}
	if (_playTime == 0){
		//������ֱ�
		//changescene(���ӿ���ȭ��)
		exit(0);
	}
}

void Rect::Render()
{
	Rectangle(getMemDC(), _rc);
	char str[128];
	sprintf(str, "�÷���Ÿ�� : %d", _playTime);
	TextOut(getMemDC(), 0, 200, str, strlen(str));
	
	//���ڰ���
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
	//1���ڸ�
	if(����<10){
	�̹���->�����ӷ���(getmemDC(), ��ġ, ����,0)
	}
	//10���ڸ�
	if(����>=10 && ����<100){
	����-����%10/10
	����%10
	}
	//100�� �ڸ�
	if(100 ~ 999)
	{
	(����-����%100)/100
	(����/10)%10
	����%10
	}
	//1000�� �ڸ�(õ)
	if(1000~9999){
	(����-����%1000)/1000
	(����%1000)/100
	(����%100)/10
	����%10
	}
	//10000�� �ڸ�(��)
	if(10000~100000){
	(����-����%10000)/10000
	(����%10000)/1000
	(����%1000)/100
	(����%100)/10
	����%10
	//100000�� �ڸ�(�ʸ�)
	if(100000~100000){
	(����-����%100000)/100000
	(����%100000)/10000
	(����%10000)/1000
	(����%1000)/100
	(����%100)/10
	����%10
	}
	*/
}

Rect::~Rect()
{
}
