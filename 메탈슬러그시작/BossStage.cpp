#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("보스배경", "BackGround/보스배경.bmp", 2555, 958);
	for (int i = 0; i < 11; ++i) 
	{
		char str[100];
		sprintf(str, "다리%d", i+1);
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
		//if ( ) 바닥 RECT가 카메라 RECT left 보다 작아지면
		//바닥 RECT를 다시 뒤로 보내준다.
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
