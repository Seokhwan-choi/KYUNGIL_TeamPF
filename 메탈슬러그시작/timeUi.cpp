#include "stdafx.h"
#include "timeUi.h"
#include "GameOverUi.h"
timeUi::timeUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	// �ð� ���� ���� �ʱ�ȭ
	//========================================================
	_time = 60;
	_count = 0;

	//�̹��� �ʱ�ȭ
	_timeImg = IMAGEMANAGER->addFrameImage("���ѽð�", "UI/timenumber.bmp", 510, 69, 10.1, true, RGB(255, 0, 255));
	//�Һ��� �ʱ�ȭ
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
	//4�ʸ��� 1�� �����ϵ��� �Ѵ�
	_count++;
	if (_count % 400 == 0) {
		_time--;
	}
	if (_time <= 0) {
		_time = 0;
	}
	
	if (_time <= 0) {
		//ĳ���� �����update�κ� �־��ش�.
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
