#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("�������", "BackGround/�������.bmp", 2555, 958);
	for (int i = 0; i < 11; ++i) 
	{
		char str[100];
		sprintf(str, "�ٸ�%d", i+1);
		_ground[i] = RectMakeCenter(85 + (174 * i), 750, 175, 183);
		_groundImage[i] = IMAGEMANAGER->addImage(str, string("BackGround/"+ string(str) + ".bmp").c_str(), 175, 183, true, RGB(248,0,248));
		_check[i] = false;
	}
	return S_OK;
}

void BossStage::Release(void)
{

}

void BossStage::Update(void)
{
	for (int i = 0; i < 11; ++i) 
	{
		//if ( ) �ٴ� RECT�� ī�޶� RECT left ���� �۾�����
		//�ٴ� RECT�� �ٽ� �ڷ� �����ش�.
	}
}

void BossStage::Render(void)
{
	_bgImage->render(getMemDC());
	for (int i = 0; i < 11; ++i) 
	{
		//Rectangle(getMemDC(), _ground[i]);
		_groundImage[i]->render(getMemDC(), _ground[i].left, _ground[i].top);
	}
}
