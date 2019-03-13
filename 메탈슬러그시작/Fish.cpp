#include "stdafx.h"
#include "Fish.h"
#include "Player.h"

Fish::Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}


Fish::~Fish()
{
}

HRESULT Fish::Init()
{
	//����� �ʱ�ȭ ����
	_state = state::IDLE;
	//�÷��̾� Ŭ���� �ʱ�ȭ
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�");
	//����� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 8; i++)
	{
		fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
		fish_rc[i].isFish = false;
		fish_rc[i].Imgchange = false;
		fish_rc[i].count = 1;
		fish_rc[i].fish_death = 1;
		fish_rc[i].Imgcount[0] = fish_rc[i].Imgindex[0] = 0;
		fish_rc[i].Imgcount[1] = fish_rc[i].Imgindex[1] = 0;
		fish_rc[i].Imgcount[2] = fish_rc[i].Imgindex[2] = 0;
		fish_rc[i].hp = 3;
	}
		
	
	//�Ÿ� ����
	_cam.isCrush = false;
	//ī���� �ʱ�ȭ
	count = 1;
	count_death = 1;
	//�̹��� �ʱ�ȭ
	fishImg[0] = IMAGEMANAGER->addFrameImage("fish", "Enemy/�����-1.bmp", 1200, 60, 12, 1, true, RGB(255, 0, 255));
	fishImg[1] = IMAGEMANAGER->addFrameImage("fish1", "Enemy/�����-2.bmp", 2400, 60, 24, 1, true, RGB(255, 0, 255));
	fishImg[2] = IMAGEMANAGER->addFrameImage("fish2", "Enemy/�����-3.bmp", 1300, 60, 13, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void Fish::Release()
{
}

void Fish::Update()
{
	//����� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//ī�޶� ��Ʈ
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 13.5f, _size.y);

	if (!_cam.isCrush)
	{
		_state = state::IDLE;
	}
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &player->GetRect()))
	{
		_cam.isCrush = true;
	}
	if (_cam.isCrush)
	{
		_state = state::L_MOVE;
	}
	if (_state == state::L_MOVE)
	{
		count++;
		count_death++;
		if (count % 30 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				if (fish_rc[i].isFish == true)
				{
					continue;
				}
				fish_rc[i].isFish = true;
				break;
			}
		}

		for (int i = 0; i < 8; i++)
		{
			if (fish_rc[i].isFish == true)
			{
				fish_rc[i].count++;
				fish_rc[i].Imgcount[0]++;
				if (fish_rc[i].Imgcount[0] % 8 == 0)
				{
					fish_rc[i].Imgindex[0]++;
					if (fish_rc[i].Imgindex[0] > 11)
					{
						fish_rc[i].Imgindex[0] = 11;
					}
				}
				if (fish_rc[i].Imgindex[0] == 11)
				{
					fish_rc[i].Imgchange = true;
					fish_rc[i].Imgcount[1]++;
					if (fish_rc[i].Imgcount[1] % 5 == 0)
					{
						fish_rc[i].Imgindex[1]++;
						if (fish_rc[i].Imgindex[1] > 23)
						{
							fish_rc[i].Imgindex[1] = 0;
						}
					}
				}
				if (fish_rc[i].count && fish_rc[i].count < 50)
				{
					fish_rc[i].Fish_Rc.top -= 3.5;
					fish_rc[i].Fish_Rc.bottom -= 3.5;
				}
				if (fish_rc[i].count > 50 && fish_rc[i].count < 95)
				{
					fish_rc[i].Fish_Rc.top += 3;
					fish_rc[i].Fish_Rc.bottom += 3;
					fish_rc[i].Fish_Rc.left -= 2;
					fish_rc[i].Fish_Rc.right -= 2;
				}
				if (fish_rc[i].count > 95)
				{
					fish_rc[i].Fish_Rc.left -= 5;
					fish_rc[i].Fish_Rc.right -= 5;
				}
				if (fish_rc[i].Fish_Rc.left < 0)
				{
					fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
					fish_rc[i].count = 0;
					fish_rc[i].Imgcount[0] = 0;
					fish_rc[i].Imgindex[0] = 0;
					fish_rc[i].Imgcount[1] = 0;
					fish_rc[i].Imgindex[1] = 0;
					fish_rc[i].Imgchange = false;
				}
			}
		}
	}

	//���� ó��
	for (int i = 0; i < 8; i++)
	{
		if (fish_rc[i].hp <= 0)
		{
			fish_rc[i].hp = 0;
		}
	}
	//if (count_death % 100 == 0)
	//{
	//	_state = state::L_IDLE;
	//}
	//if (_state == state::L_IDLE)
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		if (fish_rc[i].isFish == true)
	//		{
	//			
	//			fish_rc[i].Imgcount[2]++;
	//			if (fish_rc[i].Imgcount[2] % 3 == 0)
	//			{
	//				fish_rc[i].Imgindex[2]++;
	//				if (fish_rc[i].Imgindex[2] > 12)
	//				{
	//					fish_rc[i].Imgindex[2] = 0;
	//				}
	//			}
	//			fish_rc[i].fish_death++;
	//		}
	//		if (fish_rc[i].fish_death % 100 == 0)
	//		{
	//			fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
	//			fish_rc[i].Imgcount[2] = 0;
	//			fish_rc[i].Imgindex[2] = 0;
	//			fish_rc[i].count = 0;
	//			fish_rc[i].Imgcount[0] = 0;
	//			fish_rc[i].Imgindex[0] = 0;
	//			fish_rc[i].Imgcount[1] = 0;
	//			fish_rc[i].Imgindex[1] = 0;
	//			fish_rc[i].Imgchange = false;
	//		}
	//	}	
	//}
	
}

void Fish::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);
	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);
	//����� ��Ʈ �׸���
	for (int i = 0; i < 8; i++)
	{
		if (_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == false)
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[0]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5, fish_rc[i].Fish_Rc.top - 5,fish_rc[i].Imgindex[0],1);
		}
		if (_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == true)
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[1]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 8, fish_rc[i].Fish_Rc.top - 8, fish_rc[i].Imgindex[1], 1);
		}
		//if (_state == state::L_IDLE)
		//{
		//	fishImg[2]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5, fish_rc[i].Fish_Rc.top - 5, fish_rc[i].Imgindex[2], 1);
		//}
	}
}
