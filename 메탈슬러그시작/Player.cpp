#include "stdafx.h"
#include "Player.h"
// �ڽ��� ������ ���ؼ� �θ���� �ʿ���
// ������;���
//��ǻ� ���� ȭ�� ���� ���� Ŭ����
Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// Ŭ���� �̸� ���� ���ش�.
	_position = pos;			// ��ǥ �ʱ�ȭ ���ش�.
	_size = size;				// ������ �ʱ�ȭ ���ش�.
	_pivot = Pivot::LeftTop;	// �ǹ� ��ġ ����ش�.
	//this->UpdateRectByPivot();	// RECT �׷��ش�.
	_isActive = true;			// Ȱ��ȭ �Ǿ��ִ�. 
	_isLive = true;				// ��� �ִ�.
	_center = { WINSIZEX / 4 - WINSIZEX / 8, WINSIZEY / 2 };
	//4�� ��Ʈ ��ġ
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
	_mainSceneTime = 30;		//���ѽð�
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

	//���� ��Ʈ ���� �Ѿ�� �ʰ� ��ġ ����ְ� �����̱�
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
	//���� ������ �ö� ��Ʈ �������ֱ�
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

	//������ ��Ʈ�� ��� �÷��ֱ�
	if (_goUp[a] == true)
	{
		gameStartRc[a].bottom -= 10;
		gameStartRc[a].top -= 10;
		gameStartRc[4].top -= WINSIZEY;
		gameStartRc[4].bottom -= WINSIZEY;
		_isShow = true;
	}
	this->UpdateRectByPivot();	// RECT �׷��ش�.

	if (_isShow == true )
	{
		if (_time == 500)
		{
			SCENEMANAGER->ChangeScene("��������2");
		}
		
	}


}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);
	//������ ��Ʈ 4�� �̵��� ��Ʈ 1�� 
	for (int i = 0; i < 5; i++)
	{
		Rectangle(getMemDC(), gameStartRc[i]);
	}
	RECT temp;
	//���� ��Ʈ �����̸� �ε����� �׷��شٰ� ����
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

