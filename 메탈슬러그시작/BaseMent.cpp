#include "stdafx.h"
#include "BaseMent.h"

HRESULT BaseMent::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("���Ϲ��", "BackGround/���Ϻ��̽�.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("���Ϲ���ȼ�", "BackGround/���Ϻ��̽��ȼ�.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("�볪��", "BackGround/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));


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
		IMAGEMANAGER->findImage("�볪��")->setFrameX(_index);
		// �̹��� ������ ������ �����ϸ� ������ �ε��� ����
		if (_index == 21) {
			_index--;
		}
	}
}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### ���� ī�޶� ���� �ȵ���. ##############
	// =======================================================
	_bgImage->render(getMemDC());
	_Out->frameRender(getMemDC(), 250, 390);

	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}
