#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"


HRESULT StageOne::Init(void)
{
	_player = new Player("플레이어", { 500,0 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	//작은게 수
	_crabCount = 11;
	//작은게 초기화
	for (int i = 0; i < _crabCount; i++)
	{
		string num = to_string(i);
		string name = "crab" + num;

		_crab[i] = new Crab(name, { 2000.f + (i * 350.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		if (i == 4)
		{
			_crab[i] = new Crab(name, { 4500.f, WINSIZEY / 2 - 50.f}, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_crab[i] = new Crab(name, { 4700.f, WINSIZEY / 2 - 50.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 6)
		{
			_crab[i] = new Crab(name, { 5100.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 7)
		{
			_crab[i] = new Crab(name, { 5300.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 8)
		{
			_crab[i] = new Crab(name, { 5600.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 9)
		{
			_crab[i] = new Crab(name, { 10300.f, WINSIZEY / 2 + 150.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 10)
		{
			_crab[i] = new Crab(name, { 10500.f, WINSIZEY / 2 + 150.f }, { 100, 150 }, GameObject::Pivot::Center);
		}

		_crab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab[i]);
	}

	//거품게 수
	_bubbleCrabCount = 8;
	//거품게 초기화
	for (int i = 0; i < _bubbleCrabCount; i++)
	{
		string num = to_string(i);
		string name = "bubbleCrab" + num;

		_bubbleCrab[i] = new BubbleCrab(name, { 3400.f + (i * 100.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);

		if (i == 3)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 7400.f + (i * 100.f), WINSIZEY / 2 - 250 }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 4)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 7600.f + (i * 100.f), WINSIZEY / 2 - 250 }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 8200.f + (i * 100.f), WINSIZEY / 2 - 120 }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 6)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 9000.f + (i * 100.f), WINSIZEY / 2 - 120 }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 7)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 9200.f + (i * 100.f), WINSIZEY / 2 - 120 }, { 100, 150 }, GameObject::Pivot::Center);
		}

		_bubbleCrab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab[i]);
	}

	//잠자리 수
	_flyBugCount = 2;
	//잠자리 초기화
	for (int i = 0; i < _flyBugCount; i++)
	{
		string num = to_string(i);
		string name = "_flyBug" + num;
		
		_flyBug[i] = new FlyBug(name, { 1500.f, 130.f }, { 200, 100 }, GameObject::Pivot::Center);
		
		/*if (i == 2)
		{
			_flyBug[i] = new FlyBug(name, { 15500.f + (i * 250.f), 150.f }, { 200, 100 }, GameObject::Pivot::Center);
		}
		else if (i == 3)
		{
			_flyBug[i] = new FlyBug(name, { 15500.f + (i * 250.f), 150.f }, { 200, 100 }, GameObject::Pivot::Center);
		}
		else if (i == 4)
		{
			_flyBug[i] = new FlyBug(name, { 16000.f + (i * 250.f), 150.f }, { 200, 100 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_flyBug[i] = new FlyBug(name, { 16000.f + (i * 250.f), 150.f }, { 200, 100 }, GameObject::Pivot::Center);
		}*/
		_flyBug[i]->Init();

		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug[i]);
	}
	//_bigCrab = new BigCrab("crab", { 2060, WINSIZEY / 2 + 110 }, { 200, 280 }, GameObject::Pivot::Center);
	//_bigCrab->Init();
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bigCrab);


	//잠자리 생성
	//FlyBug* _flyBug = new FlyBug("flyBug", { 1060, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
	//_flyBug->Init();
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug);


	
	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);
	//
	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);
	//
	
	//
	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);
	//
	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);
	


	OldMan* _oldman = new OldMan("oldman1", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman);

	//OldMan* _oldman2 = new OldMan("oldman2", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::TIED, ITEM::HEAVY);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman2);

	OldMan* _oldman3 = new OldMan("oldman3", { 2000, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::RUMI, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::UI, _oldman3);

	ItemUi* _item = new ItemUi("item", {WINSIZEX,WINSIZEY/2}, { 50,50 }, GameObject::Pivot::LeftTop, ITEM::FISH);
	OBJECTMANAGER->AddObject(ObjectType::UI, _item);

	//totalScore* _total = new totalScore("total", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _total);

	//_test = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 250, 250);
	_bgImage = IMAGEMANAGER->findImage("배경");
	_bgSea = IMAGEMANAGER->findImage("배경출렁");
	_wallImage = IMAGEMANAGER->findImage("맵장벽");
	_bgImage2 = IMAGEMANAGER->findImage("배경의배경");
	_PixelImage = IMAGEMANAGER->findImage("배경픽셀");
	_tongImage = IMAGEMANAGER->findImage("통");

	_wallRect = RectMakeCenter(6750, WINSIZEY/2, 50, 1500);

	_index = 0;
	_count = 0;

	_index2 = 0;
	_count2 = 0;

	_index3 = 0; 
	_count3 = 0;

	_crush = false;


	//#####################################테스트용랙트 

	_testRect = RectMake(13095, 260, 160, 50);

	return S_OK;
}

void StageOne::Release(void)
{
	OBJECTMANAGER->Release();
}

void StageOne::Update(void)
{
	OBJECTMANAGER->Update();
	CAMERA->SetCamera(_player->GetPosition());
	
	_count++;
	if (_count % 10 == 0) {
		_index++;
		if (_index > 7) {
			_index = 0;
		}
		IMAGEMANAGER->findImage("배경출렁")->setFrameX(_index);
	}

	//_count2++; //6000 정도 도달하면 뭄이 열리게 하면된다  
	//if (_count2 % 10 == 0) {
	//	_index2++;
	//	if (_index2 > 6) {
	//		_index2 = 0;
	//	}
	//	IMAGEMANAGER->findImage("맵장벽")->setFrameX(_index2);
	//}

	if (_player->GetCollisionPlayer().right > 6200)
	{
		_count2++; //6000 정도 도달하면 뭄이 열리게 하면된다  
		if (_count2 % 10 == 0)
		{
			_index2++;
			if (_index2 > 6) {
				_index2 = 5;
			}
			IMAGEMANAGER->findImage("맵장벽")->setFrameX(_index2);
			}
		}

	// F1 눌러서 픽셀좀 보쟝 
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_PixelCheck = !_PixelCheck;
		_crush = !_crush;
	}

	//CAMERA->SetCamera(_player->GetPosition());

	if (_crush) {
		RECT _temp;
		if (IntersectRect(&_temp, &_player->GetRect(), &_wallRect)) {
			_player->SetPosition({
				_wallRect.left - (_player->GetSize().x / 2.0f),
				_player->GetPosition().y });
		}
		//CAMERA->SetCamera(_player->GetPosition());
	}
	this->PlayerBulletCollisionEnemy(); //플레이어 총알과 몬스터 충돌시 
	this->PlayerCollisionEnemy(); //플레이어 몸통과 애너미 충돌시 
	this->PlayerBoomCollisionBoom(); //플레이어 수류탄과  애너미 충돌시 
	this->ChangeMap(); 
}

void StageOne::Render(void)
{
	_bgImage2->render(getMemDC(), 0 - (CAMERA->GetCamera().left / 2), -310 - CAMERA->GetCamera().top);
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left - 300, -135 - CAMERA->GetCamera().top);
	_bgSea->frameRender(getMemDC(), 0 - CAMERA->GetCamera().left - 300, WINSIZEY - 278 - CAMERA->GetCamera().top);
	
	if (_PixelCheck) {
		_PixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left - 300, -135 - CAMERA->GetCamera().top);
		_wallImage->frameRender(getMemDC(), 5850 - CAMERA->GetCamera().left, 0 - CAMERA->GetCamera().top);
		_tongImage->frameRender(getMemDC(), 13000 - CAMERA->GetCamera().left - 300, -65 - CAMERA->GetCamera().top);
	}

	

	//#################################테스트###############33
	RECT test = CAMERA->Relative(_testRect);
	Rectangle(getMemDC(), test);


	OBJECTMANAGER->Render();
	//RECT _WALL = CAMERA->Relative(_wallRect);
	//Rectangle(getMemDC(), _WALL);
}

void StageOne::PlayerBulletCollisionEnemy()
{
	// _player _crab 
	RECT temp; 


	//############################################애너미 2번쨰 랙트랑충돌
	//#######################일반총알 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab[j]->getCol(2)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}
	//###########################해비머신건 총알 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab[j]->getCol(2)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}
	

	//############################################애너미 1번쨰 랙트랑충돌
	//#######################일반총알 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab[j]->getCol(1)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}
	//###########################해비머신건 총알 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab[j]->getCol(1)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}


	//############################################애너미 3번쨰 랙트랑충돌
	//#######################일반총알 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab[j]->getCol(3)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}
	//###########################해비머신건 총알 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab[j]->getCol(3)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}



	//############################################애너미 4번쨰 랙트랑충돌
	//#######################일반총알 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab[j]->getCol(4)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}
	//###########################해비머신건 총알 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab[j]->getCol(4)))
			{
				_crab[j]->crab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}
	}


}

void StageOne::PlayerCollisionEnemy()//플레이어 몸통과 애너미 몸통과 충돌햇을시 
{
	RECT temp;

	for (int i = 0; i < _crabCount; i++)
	{
		if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(2)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
		{//100 140사이즈크기 플레이어 
		 // Crab  left와비교 
			cout << "충돌" << endl;
			_player->SetPosition({ (float)_crab[i]->getCol(2).left - 180, (float)_player->GetPosition().y });

		}
		else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(3)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
		{//100 140사이즈크기 플레이어 
		//Crab right와 비교 
			cout << "충돌" << endl;
			_player->SetPosition({ (float)_crab[i]->getCol(2).right + 170, (float)_player->GetPosition().y });
		}
		//만약에 크랩의 맨위와 플레이어가 충돌햇을시 
		else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(0)))
		{
			_player->SetJumppower(7.5f);

			//cout << "충돌" << endl; 
			//_player->
			if (!_player->GetIsleft())          //위에랙트랑 충돌햇는데 만약 오른쪽상태일시 
			{
				_player->SetPosition({ (float)_player->GetPosition().x - 10,(float)_player->GetPosition().y - 10 });
			}
		}
	}
	//else if(IntersectRect(&temp, &_player->GetCollisionPlayer(),&_crab->getCol))


}

void StageOne::PlayerBoomCollisionBoom()
{
	RECT temp; 
	for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	{
		if (_player->playerboom()->getVBoom()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab[j]->getCol(2)))
			{
				_crab[j]->crab_damage(1);
				_player->playerboom()->SetisFire(i, false);
				cout << "박음" << endl;
				cout << &_player->playerboom()->getVBoom()[i].rc.right << endl;
				break;
			}
		}
	}
	for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	{
		if (_player->playerboom()->getVBoom()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab[j]->getCol(3)))
			{
				_crab[j]->crab_damage(1);
				_player->playerboom()->SetisFire(i, false);
				cout << &_player->playerboom()->getVBoom()[i].rc.right << endl;
				break;
			}
		}
	}

	//for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	//{
	//	if (_player->playerboom()->getVBoom()[i].isFire == false)continue;
	//	if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab->getCol(1)))
	//	{
	//		_crab->Damage(1);
	//		//_player->playerbullet()->getVBullet()[i].isFire = false;
	//	//	_player->SetBoomredner(true);
	//	//	cout << "충돌" << endl;
	//		break;
	//	}
	//}
	//for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	//{
	//	if (_player->playerboom()->getVBoom()[i].isFire == false)continue;
	//	if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab->getCol(3)))
	//	{
	//		_crab->Damage(1);
	//		//_player->playerbullet()->getVBullet()[i].isFire = false;
	//
	//		//_player->SetBoomredner(true);
	//		break;
	//	}
	//}

}

void StageOne::ChangeMap()
{
	if (_player->GetCollisionPlayer().right > _testRect.left &&
		_player->GetCollisionPlayer().left < _testRect.right &&
		_player->GetCollisionPlayer().top < _testRect.bottom)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			SCENEMANAGER->ChangeScene("지하스테이지");
		}
	}
}

