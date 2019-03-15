#include "stdafx.h"
#include "startUi.h"



startUi::startUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	// �����׾� �ʱ�ȭ( size : 1280x960 )
	//========================================================
	_name = name;
	_position = pos; //�߽ɰ����� ����ش�
	_size = size;    //winsizex, winsizey
	_pivot = Pivot::Center;
	
	//========================================================
	// �����׾� �̹��� �ʱ�ȭ( size : 1280x960 )
	//========================================================
	_startBgImage = IMAGEMANAGER->findImage("startScene");
	
	//========================================================
	// ������ ���� ���� �ʱ�ȭ( size : 1280x960 )
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
	//0.5�ʸ��� �ٲ���
	_startBgImage->setFrameY(0);
	if (_count % 30 == 0) {
		_index++;
		if (_index > 1) {
			_index = 0;
		}
		_startBgImage->setFrameX(_index);
	}
	//���ͽ� ���� ĳ���� ����â���� �̵��Ѵ�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->ChangeScene("ĳ���ͼ���ȭ��");
	}

	
}

void startUi::Render()
{
	_startBgImage->frameRender(getMemDC(), _rc.left, _rc.top);
}
