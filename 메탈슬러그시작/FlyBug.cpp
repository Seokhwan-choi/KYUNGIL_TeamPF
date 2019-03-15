#include "stdafx.h"
#include "FlyBug.h"
#include "Player.h"

FlyBug::FlyBug(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

FlyBug::~FlyBug()
{
}

HRESULT FlyBug::Init()
{
	//상태 초기화
	//_state = state::IDLE;
	//상하 움직임 처리를 위한 변수 초기화
	_move = 0;
	_isUp = false;
	//공격 처리를 위한 변수
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	//체력 초기화
	_hp = 3;

	//잠자리 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}
	//죽음 처리를 위한 변수
	_deathTimer = 0;
	//잠자리 카메라 렉트(항상 몸 중앙을 따라 다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, 500, 550);
	//플레이어 클래스 초기화
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "플레이어");
	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//잠자리 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x + _size.y / 2, _col.pt.y, _size.x, _size.y / 2);
	//잠자리 이미지 초기화
	_flyBugImg[0] = IMAGEMANAGER->findImage("flybug");
	_flyBugImg[1] = IMAGEMANAGER->findImage("flybug1");
	_flyBugImg[2] = IMAGEMANAGER->findImage("flybug2");
	_flyBugImg[3] = IMAGEMANAGER->findImage("flybug3");
	_flyBugImg[4] = IMAGEMANAGER->findImage("flybug4");

	for (int i = 0; i < 5; i++)
	{
		_index[i] = 0;
		_countImg[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		_alpha[i] = 255;
	}

	//플레이어와 거리 계산
	_dist = GetDistance(_cam.pt.x, _cam.pt.y, _player->GetPosition().x, _player->GetPosition().y);

	//다시 돌아갈 위치 설정
	_tempPt = { _position.x, _position.y };
	//처음 생성좌표와 거리 계산
	_tempDist = GetDistance(_position.x, _position.y, _tempPt.x, _tempPt.y);
	count = 0;
	return S_OK;
}

void FlyBug::Release()
{
}

void FlyBug::Update()
{
	//마우스 좌표 담기
	//_pt.x = _ptMouse.x;
	//_pt.y = _ptMouse.y;
	//처음 생성좌표와 거리 계산
	_tempDist = GetDistance(_position.x, _position.y, _tempPt.x, _tempPt.y);
	_dist = GetDistance(_cam.pt.x, _cam.pt.y, _player->GetPosition().x, _player->GetPosition().y);

	_countImg[0]++;
	if (_countImg[0] % 1 == 0)
	{
		_index[0]++;
		if (_index[0] > 23)
		{
			_index[0] = 0;
		}
	}

	//잠자리 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//잠자리 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + 50 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//잠자리 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 2.f, _size.y);

	//잠자리 충돌 렉트(항상 몸을 따라 다닌다.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x, _col.pt.y, _size.x, _size.y);

	//플레이어와 각도 체크
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	if ((_cam.rc.left >= _player->GetPosition().x - 600
		|| _cam.rc.right <= _player->GetPosition().x + 600)
		&& _tempDist >= 50)
	{
		_state = state::IDLE;
		//cout << "idle" << endl;
	}

	//270도보다 크면 왼쪽으로 이동
	if (_angle > PI / 180 * 270 
		&& _cam.rc.left > _player->GetPosition().x -600)
	{
		_state = state::L_MOVE;
		

	}
	//270도 보다 작으면 오른쪽으로 이동
	else if (_angle < PI / 180 * 270 
		&& _cam.rc.right < _player->GetPosition().x + 600)
	{
		_state = state::R_MOVE;
		
	}

	//공격 게이지 5번 모으면 그때 공격 상태로 변경
	if (_gauge % 5 == 0 
	{
		_state = state::ATTACK;
		
	}

	//플레이어와 충돌 체크
	if (GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y)
		< _size.x / 2 + _player->GetSize().x / 2)
	{
		_isAttack = true;
	}

	//플레이어 총알과 충돌 체크
	if (KEYMANAGER->isToggleKey('R') || _hp <= 0)
	{
		_state = state::DEATH;
	}

	//이동 테스트
	/*if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
	   _position.x -= 5.f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
	   _position.x += 5.f;
	}*/
	//상태 따른 움직임 처리
	switch (_state)
	{
	//대기 상태
	case state::IDLE:

		//아래로 이동
		if (!_isUp)
		{
			//_position.x += 2.f;
			_position.y += 5.f;
			_move += 1;
			//cout << _move << endl;
		}
		//위로 이동
		else
		{
			//_position.x -= 2.f;
			_position.y -= 5.f;
			_move += 1;
		}

		//25 이동시 반대로 이동
		if (_move > 16)
		{
			_move = 0;
			_isUp = !_isUp;
			_gauge++;
			cout << _gauge << endl;
		}

		break;
		//공격 상태
	case state::ATTACK:
		cout << "A_pika" << endl;
		_countImg[1]++;
		if (_countImg[1] % 1 == 0)
		{
			_index[1]++;
			if (_index[1] > 26)
			{
				_index[1] = 0;
			}
		}

		if (!_isAttack)
		{
			//플레이어를 공격 할 각도 설정
			_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
			
			_position.x += cosf(_attackAngle) * 10.f;
			_position.y += -sinf(_attackAngle) * 10.f;

		}

		//플레이어와 충돌 처리 되면 다시 원위치
		if (_isAttack)
		{
			count++;
			if (_angle < 270)
			{
				_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x - 600.f, _player->GetPosition().y - 500.f);

			}
			else if (_angle > 270)
			{
				_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x + 600.f, _player->GetPosition().y - 500.f);
			}
			_position.x -= cosf(_attackAngle) * 5.f;
			if (_cam.rc.top > 100)
			{
				_position.y += -sinf(_attackAngle) * 55.f;
			}
			if (count == 90)
			{
				count = 0;
				_gauge = 1;
				_isAttack = false;
			}
			
			

		}

		break;
		//왼쪽으로 이동 상태
	case state::L_MOVE:
		//270도보다 크면 왼쪽으로 이동
		if (GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y) > PI / 180 * 270)
		{
			if (_cam.rc.left > _player->GetPosition().x - 600.f)
			{
				_position.x -= 12.f;
			}


			if (_cam.rc.top > _player->GetPosition().y)
			{
				_position.y -= 5.f;
			}
		}
		cout << "L_pika" << endl;
		break;
		//오른쪽으로 이동 상태
	case state::R_MOVE:
		//270도 보다 작으면 오른쪽으로 이동
		if (GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y) < PI / 180 * 270)
		{
			if (_cam.rc.right < _player->GetPosition().x + 600.f)
			{
				_position.x += 12.f;
				cout << "R_pika" << endl;
			}

			if (_cam.rc.top > 100)
			{
				_position.y -= 5.f;
			}
		}
		
		break;
		//죽음 상태
	case state::DEATH:

		_countImg[2]++;
		if (_countImg[2] % 5 == 0)
		{
			_index[2]++;
			if (_index[2] > 29)
			{
				_index[2] = 29;
			}
		}
		if (_index[2] == 29)
		{
			_alpha[1] -= 3;
			if (_alpha[1] <= 0)
			{
				_alpha[1] = 0;
			}
		}
		_countImg[3]++;
		if (_countImg[3] % 5 == 0)
		{
			_index[3]++;
			if (_index[3] > 12)
			{
				_index[3] = 0;
			}
		}
		_countImg[4]++;
		if (_countImg[4] % 5 == 0)
		{
			_index[4]++;
			if (_index[4] > 12)
			{
				_index[4] = 0;
			}
		}
		//충돌 렉트 없애기
		_col.rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

		if (_position.y + _size.y / 2 < WINSIZEY)
		{
			//시체 부분 떨어뜨리기
			_position.y += 5.f;
		}
		//땅에 도착했을 때
		if (_position.y + _size.y / 2 >= WINSIZEY)
		{
			_index[3] = 12;
			if (_index[3] == 12)
			{
				_alpha[0] -= 50;
				if (_alpha[0] <= 0)
				{
					_alpha[0] = 255;
				}
			}
			_index[4] = 12;
			if (_index[4] == 12)
			{
				_alpha[2] -= 50;
				if (_alpha[2] <= 0)
				{
					_alpha[2] = 255;
				}
			}
			_deathTimer++;

			if (_deathTimer % 100 == 0)
			{
				OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "flyBug"));
			}
		}

		break;
	}

}

void FlyBug::Render()
{
	//카메라 렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));
	//렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_rc));
	if (((_state == state::IDLE && _angle > PI / 180 * 270) || _state == state::L_MOVE) && !(_state == state::ATTACK) && !(_state == state::DEATH))
	{
		_flyBugImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[0], 0);
	}
	if (((_state == state::IDLE && _angle < PI / 180 * 270) || _state == state::R_MOVE) && !(_state == state::ATTACK))
	{
		_flyBugImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[0], 1);
	}
	if (_state == state::ATTACK && _angle > PI / 180 * 270)
	{
		_flyBugImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[1], 0);
	}
	if (_state == state::ATTACK && _angle < PI / 180 * 270)
	{
		_flyBugImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[1], 1);
	}

	//충돌렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_col.rc));
	//시체처리렉트 그리기
	for (int i = 0; i < 3; i++)
	{
		//Rectangle(getMemDC(), CAMERA->Relative(_part[i].rc));
		if (_state == state::DEATH)
		{
			_flyBugImg[2]->alphaFrameRender(getMemDC(), _part[1].rc.left - CAMERA->GetCamera().left - 300, _part[1].rc.top - CAMERA->GetCamera().top, _index[2], 0, _alpha[1]);
			_flyBugImg[3]->alphaFrameRender(getMemDC(), _part[2].rc.left + 80 - CAMERA->GetCamera().left - 300, _part[2].rc.top + 20 - CAMERA->GetCamera().top, _index[3], 0, _alpha[0]);
			_flyBugImg[4]->alphaFrameRender(getMemDC(), _part[0].rc.left + 130 - CAMERA->GetCamera().left - 300, _part[0].rc.top + 20 - CAMERA->GetCamera().top, _index[4], 0, _alpha[2]);
		}
	}
}