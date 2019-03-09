#include "stdafx.h"
#include "Player.h"
// 자식이 나오기 위해선 부모님이 필요행
// 데리고와야해
//사실상 메인 화면 씬을 위한 클래스
Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// 클래스 이름 설정 해준다.
	_position = pos;			// 좌표 초기화 해준다.
	_size = size;				// 사이즈 초기화 해준다.
	_pivot = Pivot::LeftTop;	// 피벗 위치 잡아준다.
	//this->UpdateRectByPivot();	// RECT 그려준다.
	_isActive = true;			// 활성화 되어있다. 
	_isLive = true;				// 살아 있다.
	_center = { WINSIZEX / 4 - WINSIZEX / 8, WINSIZEY / 2 };
	//4개 렉트 위치
	for (int i = 0; i < 4; i++)
	{
		gameStartRc[i] = RectMake(WINSIZEX / 4 * i, 0, WINSIZEX / 4, WINSIZEX);
	}
	for (int i = 0; i < 4; i++)
	{
		_isCheck[i] = false;
		_goUp[i] = false;
	}
	a = 0;
	_isShow = false;
	gameStartRc[4] = RectMake(_center.x, _center.y, 30, 30);
	_time = 0;					
	_mainSceneTime = 30;		//제한시간
}

Player::~Player()
{
}

HRESULT Player::Init()
{
	return S_OK;
}

void Player::Release()
{

}

void Player::Update()
{
	_time++;
	if (_time % 100 == 0)
	{
		_mainSceneTime --;
	}

	//작은 렉트 범위 넘어가지 않게 위치 잡아주고 움직이기
	if ( KEYMANAGER->isOnceKeyDown(VK_RIGHT) && gameStartRc[4].right < WINSIZEX - WINSIZEX/4)
	{
		gameStartRc[4].left += WINSIZEX / 4;
		gameStartRc[4].right += WINSIZEX / 4;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && gameStartRc[4].left >WINSIZEX/4)
	{
		gameStartRc[4].left -= WINSIZEX / 4;
		gameStartRc[4].right -= WINSIZEX / 4;
	}
	//엔터 누를시 올라갈 렉트 선정해주기
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		for (int i = 0; i < 4; i++)
		{
			if (_isCheck[i] == true)
			{
				gameStartRc[i].bottom -= 10;
				gameStartRc[i].top -= 10;
				a = i;
				_goUp[a] = true;
			}
		}
	}
	if (_mainSceneTime == 0) {
		for (int i = 0; i < 4; i++)
		{
			if (_isCheck[i] == true)
			{
				gameStartRc[i].bottom -= 10;
				gameStartRc[i].top -= 10;
				a = i;
				_goUp[a] = true;
			}
		}
	}

	//선정한 렉트로 계속 올려주기
	if (_goUp[a] == true)
	{
		gameStartRc[a].bottom -= 10;
		gameStartRc[a].top -= 10;
		gameStartRc[4].top -= WINSIZEY;
		gameStartRc[4].bottom -= WINSIZEY;
		_isShow = true;
	}
	this->UpdateRectByPivot();	// RECT 그려준다.

	if (_isShow == true )
	{
		if (_time == 500)
		{
			SCENEMANAGER->ChangeScene("스테이지2");
		}
		
	}


}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);
	//보여줄 렉트 4개 이동할 렉트 1개 
	for (int i = 0; i < 5; i++)
	{
		Rectangle(getMemDC(), gameStartRc[i]);
	}
	RECT temp;
	//작은 렉트 움직이며 부딪히면 그려준다고 선언
	for (int i = 0; i < 4; i++)
	{
		if (IntersectRect(&temp, &gameStartRc[i], &gameStartRc[4]))
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
			FillRect(getMemDC(), &gameStartRc[i], brush);
			_isCheck[i] = true;
			
			DeleteObject(brush);
		}
	}

	char str[128];
	sprintf(str, "%d", _mainSceneTime);
	TextOut(getMemDC(), 0, 200, str, strlen(str));
}

