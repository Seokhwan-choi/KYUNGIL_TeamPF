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
		fish_rc[i].hp = 1;
		fish_rc[i].isDeath = false;
	}
	_rc_on = true;
	is = true;
	//�Ÿ� ����
	_cam.isCrush = false;
	//ī���� �ʱ�ȭ
	count = 1;
	count_death = 1;
	boxhp = 10;
	//�̹��� �ʱ�ȭ
	fishImg[0] = IMAGEMANAGER->findImage("fish1");
	fishImg[1] = IMAGEMANAGER->findImage("fish2");
	fishImg[2] = IMAGEMANAGER->findImage("fish3");
	fish_box = IMAGEMANAGER->findImage("fishbox");

	//�ݺ��Ҹ� ������ ���� ����
	_deathSound = false;

	return S_OK;
}

void Fish::Release()
{
}

void Fish::Update()
{
	RECT temp;
	for (int i = 0; i < 8; i++)
	{
		if (IntersectRect(&temp, &player->GetRect(), &fish_rc[i].Fish_Rc))
		{
			//exit(0);
		}
	}

	if (_rc_on == true)
	{
		if (is == true)
		{
			//����� ��Ʈ
			_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
			//ī�޶� ��Ʈ
			_cam.pt = { _position.x, _position.y };
			_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 13.5f, _size.y);
		}
		if (!_cam.isCrush)
		{
			_state = state::IDLE;
		}
		RECT rcCam;
		if (IntersectRect(&rcCam, &_cam.rc, &player->GetRect()))
		{
			_cam.isCrush = true;
		}
		else
		{
			_cam.isCrush = false;
		}
		if (_cam.isCrush)
		{
			_state = state::L_IDLE;
		}
		if (_state == state::L_IDLE)
		{
			count++;
			if (count % 30 == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					if (fish_rc[i].isFish == true)
					{
						continue;
					}
					fish_rc[i].isFish = true;
					fish_rc[i]._fish_state = state::L_MOVE;
					break;
				}
			}
		}

		for (int i = 0; i < 8; i++)
		{
			if (fish_rc[i]._fish_state == state::L_MOVE)
			{

				if (fish_rc[i].isFish == false)
				{
					continue;
				}
				else
				{
					break;
				}
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
				if (fish_rc[i].count > 0 && fish_rc[i].count < 50)
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
				if (fish_rc[i].count > 95 && !(fish_rc[i]._fish_state == state::L_DEATH))
				{
					fish_rc[i].Fish_Rc.left -= 5;
					fish_rc[i].Fish_Rc.right -= 5;
				}
				if (fish_rc[i].Fish_Rc.left < 0)
				{
					//fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
					fish_rc[i].count = 0;
					fish_rc[i].Imgcount[0] = 0;
					fish_rc[i].Imgindex[0] = 0;
					fish_rc[i].Imgcount[1] = 0;
					fish_rc[i].Imgindex[1] = 0;
					fish_rc[i].Imgchange = false;
					fish_rc[i].isFish = false;
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
		for (int i = 0; i < 8; i++)
		{
			if (KEYMANAGER->isToggleKey('F')  || fish_rc[i].hp <= 0) //|| fish_rc[i].hp <= 0)
			{
				//_state = state::L_DEATH;
			//	fish_rc[0].isDeath = true;
				fish_rc[1].isDeath = true;
			//	fish_rc[2].isDeath = true;
			//	fish_rc[3].isDeath = true;
			}
			//}
			if (!_deathSound && fish_rc[i].isDeath)
			{
				//�״� �Ҹ�
				SOUNDMANAGER->play("���������");
				_deathSound = true;
			}

			//for (int i = 0; i < 8; i++)
			//{
			//	if (_state == state::L_DEATH)
			//	{
			//		if (fish_rc[i].isDeath == true)
			//		{
			//			continue;
			//		}
			//		fish_rc[i].isDeath = true;
					if (fish_rc[i].isDeath == true)
					{
						fish_rc[i]._fish_state = state::L_DEATH;
					}
			//	}
				//break;
			//}

			for (int i = 0; i < 8; i++)
			{
				if (fish_rc[i]._fish_state == state::L_DEATH)
				{
					fish_rc[i].count = -1;
					if (fish_rc[i].isFish == true && fish_rc[i].isDeath == true)
					{
						fish_rc[i].Imgcount[2]++;
						if (fish_rc[i].Imgcount[2] % 5 == 0)
						{
							fish_rc[i].Imgindex[2]++;
							if (fish_rc[i].Imgindex[2] > 12)
							{
								fish_rc[i].Imgindex[2] = 12;
							}
						}
						fish_rc[i].fish_death++;
					}
					if (fish_rc[i].fish_death % 100 == 0)
					{
						fish_rc[i].Fish_Rc = RectMakeCenter(-1000.f, -1000.f, 50, 50);
						fish_rc[i].count = 0;
						fish_rc[i].Imgcount[0] = 0;
						fish_rc[i].Imgindex[0] = 0;
						fish_rc[i].Imgcount[1] = 0;
						fish_rc[i].Imgindex[1] = 0;
						fish_rc[i].Imgchange = false;
						fish_rc[i].isFish = false;
						fish_rc[i].isDeath = false;
					}
				}
			}
		}
		if (boxhp < 0)
		{
			boxhp = 0;
		}
		if (KEYMANAGER->isToggleKey('B') || boxhp <= 0)
		{
			is = false;
			_rc = RectMakeCenter(-1000.f, -1000.f, 50, 50);
			_cam.pt = { -1000.f,-1000.f };
			_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 13.5f, _size.y);

			for (int i = 0; i < 8; i++)
			{
				if (fish_rc[i].isFish == true)
				{
					continue;
				}
				if (fish_rc[0].isFish == false
					&& fish_rc[1].isFish == false
					&& fish_rc[2].isFish == false
					&& fish_rc[3].isFish == false
					&& fish_rc[4].isFish == false
					&& fish_rc[5].isFish == false
					&& fish_rc[6].isFish == false
					&& fish_rc[7].isFish == false
					)
				{
					_isActive = false;
				}
			}
		}
	}
}
void Fish::Render()
{
	//ī�޶� ��Ʈ �׸���
	//Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));
	
	if (is == true)
	{
		//��Ʈ �׸���
		//Rectangle(getMemDC(), CAMERA->Relative(_rc));
		fish_box->render(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top + 100- CAMERA->GetCamera().top);
	}	
	//����� ��Ʈ �׸���
	for (int i = 0; i < 8; i++)
	{
		if (fish_rc[i]._fish_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == false && !(fish_rc[i]._fish_state == state::L_DEATH))
		{
			//Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[0]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5 - CAMERA->GetCamera().left - 300, fish_rc[i].Fish_Rc.top - 5 - CAMERA->GetCamera().top,fish_rc[i].Imgindex[0],1);
		}
		if (fish_rc[i]._fish_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == true && !(fish_rc[i]._fish_state == state::L_DEATH))
		{
			//Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[1]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 8 - CAMERA->GetCamera().left - 300, fish_rc[i].Fish_Rc.top - 8 - CAMERA->GetCamera().top, fish_rc[i].Imgindex[1], 1);
		}
		if (fish_rc[i]._fish_state == state::L_DEATH && fish_rc[i].fish_death <= 40)
		{
			fishImg[2]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5 - CAMERA->GetCamera().left - 300, fish_rc[i].Fish_Rc.top - 5 - CAMERA->GetCamera().top, fish_rc[i].Imgindex[2], 1);
		}
	}
}
