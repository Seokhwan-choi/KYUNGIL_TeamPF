#include "stdafx.h"
#include "BaseMent.h"

HRESULT BaseMent::Init(void)
{
	_bgImage = IMAGEMANAGER->findImage("���Ϲ��");
	_pixelImage = IMAGEMANAGER->findImage("���Ϲ���ȼ�");
	_Out = IMAGEMANAGER->findImage("�볪��");


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
