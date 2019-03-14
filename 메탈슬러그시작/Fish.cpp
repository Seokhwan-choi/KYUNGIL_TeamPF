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
	//물고기 초기화 상태
	_state = state::IDLE;
	//플레이어 클래스 초기화
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어");
	//물고기 렉트 초기화
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
		fish_rc[i].isDeath = false;
	}
	_rc_on = true;
	is = true;
	//거리 조절
	_cam.isCrush = false;
	//카운터 초기화
	count = 1;
	count_death = 1;
	boxhp = 10;
	//이미지 초기화
	fishImg[0] = IMAGEMANAGER->addFrameImage("fish", "Enemy/물고기-1.bmp", 1200, 60, 12, 1, true, RGB(255, 0, 255));
	fishImg[1] = IMAGEMANAGER->addFrameImage("fish1", "Enemy/물고기-2.bmp", 2400, 60, 24, 1, true, RGB(255, 0, 255));
	fishImg[2] = IMAGEMANAGER->addFrameImage("fish2", "Enemy/물고기-3.bmp", 1300, 60, 13, 1, true, RGB(255, 0, 255));
	
	return S_OK;
}

void Fish::Release()
{
}

void Fish::Update()
{
	if (_rc_on == true)
	{
		if (is == true)
		{
			//물고기 렉트
			_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
			//카메라 렉트
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

		//죽음 처리
		for (int i = 0; i < 8; i++)
		{
			if (fish_rc[i].hp <= 0)
			{
				fish_rc[i].hp = 0;
			}
		}
		//for (int i = 0; i < 8; i++)
		//{
		if (KEYMANAGER->isToggleKey('R')) //|| fish_rc[i].hp <= 0)
		{
			_state = state::L_DEATH;
			fish_rc[1].isDeath = true;
		}
		//}


		for (int i = 0; i < 8; i++)
		{
			if (_state == state::L_DEATH)
			{
				if (fish_rc[i].isDeath == false)
				{
					continue;
				}
				if (fish_rc[i].isDeath == true)
				{
					fish_rc[i]._fish_state = state::L_DEATH;
				}
			}
			break;
		}

		for (int i = 0; i < 8; i++)
		{
			if (fish_rc[i]._fish_state == state::L_DEATH)
			{
				fish_rc[i].count = -1;
				if (fish_rc[i].isFish == true && fish_rc[1].isDeath == true)
				{
					fish_rc[i].Imgcount[2]++;
					if (fish_rc[i].Imgcount[2] % 3 == 0)
					{
						fish_rc[i].Imgindex[2]++;
						if (fish_rc[i].Imgindex[2] > 12)
						{
							fish_rc[i].Imgindex[2] = 12;
						}
					}
					fish_rc[i].fish_death++;
				}
				if (fish_rc[i].fish_death % 40 == 0)
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
	if (KEYMANAGER->isToggleKey('S') || boxhp <= 0)
	{
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
				OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "fish"));
			}
		}
	}
}
	


void Fish::Render()
{
	//카메라 렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));
	//렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_rc));
	//물고기 렉트 그리기
	for (int i = 0; i < 8; i++)
	{
		if (fish_rc[i]._fish_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == false && !(fish_rc[i]._fish_state == state::L_DEATH))
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[0]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5 - CAMERA->GetCamera().left, fish_rc[i].Fish_Rc.top - 5 - CAMERA->GetCamera().top,fish_rc[i].Imgindex[0],1);
		}
		if (fish_rc[i]._fish_state == state::L_MOVE && fish_rc[i].isFish == true && fish_rc[i].Imgchange == true && !(fish_rc[i]._fish_state == state::L_DEATH))
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
			fishImg[1]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 8 - CAMERA->GetCamera().left, fish_rc[i].Fish_Rc.top - 8 - CAMERA->GetCamera().top, fish_rc[i].Imgindex[1], 1);
		}
		if (fish_rc[i]._fish_state == state::L_DEATH && fish_rc[i].fish_death <= 40)
		{
			fishImg[2]->frameRender(getMemDC(), fish_rc[i].Fish_Rc.left - 5 - CAMERA->GetCamera().left, fish_rc[i].Fish_Rc.top - 5 - CAMERA->GetCamera().top, fish_rc[i].Imgindex[2], 1);
		}
	}
}
