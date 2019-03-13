#include "stdafx.h"
#include "BaseMent.h"

HRESULT BaseMent::Init(void)
{
	_bgImage = IMAGEMANAGER->findImage("지하배경");
	_pixelImage = IMAGEMANAGER->findImage("지하배경픽셀");
	_Out = IMAGEMANAGER->findImage("통나옴");


	_index = 0;	
	_count = 0;

	return S_OK;
}

void BaseMent::Release(void)
{
}

void BaseMent::Update(void)
{
	_count++;
	if (_count % 5 == 0) {
		_index++;
		if (_index > 21) 
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("통나옴")->setFrameX(_index);
		// 이미지 마지막 프레임 도달하면 프레임 인덱스 고정
		if (_index == 21) {
			_index--;
		}
	}
}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### 아직 카메라 보정 안들어갔다. ##############
	// =======================================================
	_bgImage->render(getMemDC());
	_Out->frameRender(getMemDC(), 250, 390);

	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}
