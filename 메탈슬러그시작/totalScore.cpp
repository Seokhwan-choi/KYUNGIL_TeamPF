#include "stdafx.h"
#include "totalScore.h"


totalScore::totalScore(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//구한 포로 점수 렉트 선언
	_ScoreRc = RectMake(272,444,66,68);
	//구한 포로 갯수선언
	_saveRc = RectMake(272,342,66,66);
	//만점 선언
	_milRc = RectMake(427,373,161,35);
	//포로 이미지
	_imgRc = RectMake(98,250,124,160);
	//프레임 틀
	_frameRc = RectMake(78,214,555,665);
	//엑스 렉트
	_xRc = RectMake(409, 380, 24, 24);
	//이름 렉트
	_nameRc = RectMake(110, 616, 442, 228);
	IMAGEMANAGER->addImage("점수틀", "UI/점수틀.bmp", 555, 656, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모두의이름", "UI/모두의 이름.bmp", 490, 228, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("포로오른쪽", "UI/item/captive_sirR.bmp", 2916, 150,14,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x", "UI/x.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("만", "UI/10000.bmp", 161, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("구한포로수", "UI/playerlife.bmp",660,60,10,1, true, RGB(255, 0, 255));
	

	//프레임 이미지 관련 변수 초기화
	_index =13;
	_count = 0;

	//구한숫자 초기화
	_saveNum = 0;
	_isSave = true;
}

totalScore::~totalScore()
{
}

HRESULT totalScore::Init()
{
	return S_OK;
}

void totalScore::Release()
{
}

void totalScore::Update()
{
	_count++;
	//포로 애니메이션
	IMAGEMANAGER->findImage("포로오른쪽")->setFrameY(0);
	if (_count % 8 == 0) {
		_index--;
		if (_index < 3) {
			_index = 3;
		}
		IMAGEMANAGER->findImage("포로오른쪽")->setFrameX(_index);
	}
	//구한 포로수 1씩 올려주는 처리	
	if (_isSave == true) {
		for (int i = 0; i < DATA->getCaptive(); i++) {
			if (_count % 50 == 0) {
				_saveNum += 1;
				DATA->setScore(_saveNum * 10000);
				if (_saveNum == DATA->getCaptive()) {
					_isSave = false;
					break;
				}
			}
			break;
		}
	}

}

void totalScore::Render()
{
	//이미지 랜더
	IMAGEMANAGER->frameRender("포로오른쪽", getMemDC(), _imgRc.left, _imgRc.top);
	IMAGEMANAGER->render("점수틀", getMemDC(), _frameRc.left, _frameRc.top);
	IMAGEMANAGER->render("모두의이름", getMemDC(), _nameRc.left, _nameRc.top);
	IMAGEMANAGER->render("x", getMemDC(), _xRc.left, _xRc.top);
	IMAGEMANAGER->render("만", getMemDC(), _milRc.left, _milRc.top);
	
	//1초씩 1씩 올려주도록 한다
	if (DATA->getCaptive() < 10) {
		IMAGEMANAGER->frameRender("구한포로수",getMemDC(), _saveRc.left, _saveRc.top,0,0);
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _saveRc.left + 66, _saveRc.top,_saveNum, 0);
	}
	
	//구한포로수 합산한 걸 만씩 올려주기
	int _num = 66;
	if (DATA->getCaptive() < 10) {
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _ScoreRc.left, _ScoreRc.top, _saveNum, 0);
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _ScoreRc.left + _num, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _ScoreRc.left + _num*2, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _ScoreRc.left + _num * 3, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("구한포로수", getMemDC(), _ScoreRc.left + _num * 4, _ScoreRc.top, 0, 0);
	}


}
