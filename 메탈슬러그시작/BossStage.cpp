#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("보스배경", "BackGround/보스배경.bmp", 2555, 958);
	_waterground = IMAGEMANAGER->addFrameImage("보스출렁", "BackGround/보스출렁.bmp", 10240, 100, 8, 1);
	_breakImage = IMAGEMANAGER->addImage("곧부서짐", "BackGround/곧부서짐.bmp", 875, 183, true, RGB(248, 0, 248));

	for (int i = 0; i < 11; ++i) 
	{
		char str[100];
		sprintf(str, "다리%d", i+1);
		_ground[i] = RectMake( WINSIZEX/2 + (175 * i), WINSIZEY - 215, 175, 183);
		_groundImage[i] = IMAGEMANAGER->addImage(str, string("BackGround/"+ string(str) + ".bmp").c_str(), 175, 183, true, RGB(248,0,248));
		_check[i] = true;
	}



	_start = false;
	_loopX = 0;
	_gcount = 0;
	_gframe = 0;

	return S_OK;
}

void BossStage::Release(void)
{

}

void BossStage::Update(void)
{
	// ============== 배경을 천천히 루프 시킨다. ================
	_loopX++;
	// ============== 배경바닥 출렁출렁 시킨다. =================
	_gcount++;
	if (_gcount % 5 == 0)
	{
		_gframe++;
		if (_gframe > 7) {
			_gframe = 0;
		}
		IMAGEMANAGER->findImage("보스출렁")->setFrameX(_gframe);
	}
	// ======================================================


	// ============== 배경다리 이동 및 보정 시킨다. ==================

	if (_start) 
	{
		for (int i = 0; i < 11; ++i)
		{
			_ground[i].left -= 1;
			_ground[i].right -= 1;
			if (_ground[i].right <= 0) {
				_ground[i] = RectMake(1750 - 175, WINSIZEY - 215, 175, 183);
			}
		}

		for (int i = 0; i < 11; ++i)
		{
			if (_check[i] == false)
			{
				_ground[i] = RectMake(1750 - 175, WINSIZEY - 215, 175, 183);
				_check[i] = true;
			}
		}
	}
	// =========================================================

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_start = !_start;
	}
	
}

void BossStage::Render(void)
{
	// ============== 배경을 천천히 루프 시킨다. ================
	RECT _rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_bgImage->loopRender(getMemDC(), &_rc, _loopX, 0);
	// ============== 배경바닥 출렁출렁 시킨다. =================
	_waterground->frameRender(getMemDC(), 0, WINSIZEY - 100);
	// ======================================================

	for (int i = 0; i < 11; ++i)
	{
		//Rectangle(getMemDC(), _ground[i]);
		_groundImage[i]->render(getMemDC(), _ground[i].left, _ground[i].top);
	}
	
	if (!_start)
	{
		_breakImage->render(getMemDC(), -235, WINSIZEY - 215);
	}
}
