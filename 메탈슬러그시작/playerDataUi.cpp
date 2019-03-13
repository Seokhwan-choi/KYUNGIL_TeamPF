#include "stdafx.h"
#include "playerDataUi.h"



playerDataUi::playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_bombArmsRc = RectMake(389, 33, 197, 75);
	_upRc = RectMake(215, 101, 92, 36);
	_guageRc = RectMake(203, 68, 168, 33);

	_bombarmsImg = IMAGEMANAGER->addImage("bombarms", "UI/PlayerRegardingPicture/armsbomb.bmp", 196, 74, true, RGB(255, 0, 255));
	_guageImg = IMAGEMANAGER->addImage("guagebar", "UI/PlayerRegardingPicture/guageBar.bmp", 168, 33, true, RGB(255, 0, 255));
	_1upImg = IMAGEMANAGER->addImage("1up", "UI/PlayerRegardingPicture/1up.bmp", 92, 36, true, RGB(255, 0, 255));
}

playerDataUi::~playerDataUi()
{
}

HRESULT playerDataUi::Init()
{
	return S_OK;
}

void playerDataUi::Release()
{
}

void playerDataUi::Update()
{
}

void playerDataUi::Render()
{
	_bombarmsImg->render(getMemDC(), _bombArmsRc.left, _bombArmsRc.top);
	_guageImg->render(getMemDC(), _guageRc.left, _guageRc.top);
	_1upImg->render(getMemDC(), _upRc.left, _upRc.top);
}
