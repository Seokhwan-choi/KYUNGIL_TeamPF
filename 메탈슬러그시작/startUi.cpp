#include "stdafx.h"
#include "startUi.h"



startUi::startUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	// 오프닝씬 초기화( size : 1280x960 )
	//========================================================
	_name = name;
	_position = pos; //중심값으로 잡아준다
	_size = size;    //winsizex, winsizey
	_pivot = Pivot::Center;
	
	//========================================================
	// 오프닝씬 이미지 초기화( size : 1280x960 )
	//========================================================
	_startBgImage = IMAGEMANAGER->findImage("startScene");
	
	//========================================================
	// 프레임 선택 순서 초기화( size : 1280x960 )
	//========================================================
	_count = 0;
	_index = 0;
}

startUi::~startUi()
{
}

HRESULT startUi::Init()
{
	return S_OK;
}

void startUi::Release()
{
}

void startUi::Update()
{
	_count++;
	//0.5초마다 바꿔줌
	_startBgImage->setFrameY(0);
	if (_count % 30 == 0) {
		_index++;
		if (_index > 1) {
			_index = 0;
		}
		_startBgImage->setFrameX(_index);
	}
	//엔터시 게임 캐릭터 선택창으로 이동한다
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->ChangeScene("캐릭터선택화면");
	}

	
}

void startUi::Render()
{
	_startBgImage->frameRender(getMemDC(), _rc.left, _rc.top);
}
