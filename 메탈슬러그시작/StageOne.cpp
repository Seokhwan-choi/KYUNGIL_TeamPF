#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"


HRESULT StageOne::Init(void)
{
	_player = new Player("�÷��̾�", { 500,0 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);
	//������ ��
	_crabCount = 9;
	//������ �ʱ�ȭ
	for (int i = 0; i < _crabCount; i++)
	{
		string num = to_string(i);
		string name = "crab" + num;

		_crab[i] = new Crab(name, { 2000.f + (i * 350.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		if (i == 4)
		{
			_crab[i] = new Crab(name, { 4500.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_crab[i] = new Crab(name, { 4700.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
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

		_crab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab[i]);
	}

	//��ǰ�� ��
	_bubbleCount = 3;
	//��ǰ�� �ʱ�ȭ
	for (int i = 0; i < _bubbleCount; i++)
	{
		string num = to_string(i);
		string name = "bubbleCrab" + num;

		_bubbleCrab[i] = new BubbleCrab(name, { 3400.f + (i * 100.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		_bubbleCrab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab[i]);
	}

	//_bigCrab = new BigCrab("crab", { 2060, WINSIZEY / 2 + 110 }, { 200, 280 }, GameObject::Pivot::Center);
	//_bigCrab->Init();
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bigCrab);


	//���ڸ� ����
	FlyBug* _flyBug = new FlyBug("flyBug", { 15000, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//���ڸ� ��ü �߰��ϱ�
	_flyBug->Init();
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug);

	SOUNDMANAGER->play("������������");

	
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
	
	stage1StartUi* _stage1startui = new stage1StartUi("stage1startui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _stage1startui);


	OldMan* _oldman = new OldMan("oldman1", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman);

	OldMan* _oldman2 = new OldMan("oldman2", { 2500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::TIED, ITEM::FRUIT);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman2);

	OldMan* _oldman3 = new OldMan("oldman3", { 2000, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::RUMI, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::UI, _oldman3);

	ItemUi* _item = new ItemUi("item", {WINSIZEX,WINSIZEY/2}, { 50,50 }, GameObject::Pivot::LeftTop, ITEM::FISH);
	OBJECTMANAGER->AddObject(ObjectType::UI, _item);

	//totalScore* _total = new totalScore("total", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _total);

	//_test = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 250, 250);
	_bgImage = IMAGEMANAGER->findImage("���");
	_bgSea = IMAGEMANAGER->findImage("����ⷷ");
	_wallImage = IMAGEMANAGER->findImage("���庮");
	_bgImage2 = IMAGEMANAGER->findImage("����ǹ��");
	_PixelImage = IMAGEMANAGER->findImage("����ȼ�");
	_tongImage = IMAGEMANAGER->findImage("��");
	_fade = IMAGEMANAGER->findImage("����");

	_wallRect = RectMakeCenter(6750, WINSIZEY/2, 50, 1500);

	_index = 0;
	_count = 0;

	_index2 = 0;
	_count2 = 0;

	_index3 = 0; 
	_count3 = 0;

	_crush = false;
	_check = false;

	//SOUNDMANAGER->play("������������");

	//#####################################�׽�Ʈ�뷢Ʈ 

	_testRect = RectMake(13095, 260, 160, 50);
	_fadecount = 0;
	_alpha = 255;
	_fadein = true;
	_fadeout = false;

	return S_OK;
}

void StageOne::Release(void)
{
	OBJECTMANAGER->Release();
}

void StageOne::Update(void)
{
	//����
	OBJECTMANAGER->Update();
	CAMERA->SetCamera(_player->GetPosition());

	_count++;
	if (_count % 10 == 0) {
		_index++;
		if (_index > 7) {
			_index = 0;
		}
		IMAGEMANAGER->findImage("����ⷷ")->setFrameX(_index);
	}

	//_count2++; //6000 ���� �����ϸ� ���� ������ �ϸ�ȴ�  
	//if (_count2 % 10 == 0) {
	//	_index2++;
	//	if (_index2 > 6) {
	//		_index2 = 0;
	//	}
	//	IMAGEMANAGER->findImage("���庮")->setFrameX(_index2);
	//}

	if (_player->GetCollisionPlayer().right > 6200)
	{
		_count2++; //6000 ���� �����ϸ� ���� ������ �ϸ�ȴ�  
		if (_count2 % 10 == 0)
		{
			_index2++;
			if (_index2 > 6) {
				_index2 = 5;
			}
			IMAGEMANAGER->findImage("���庮")->setFrameX(_index2);
		}
	}

	// F1 ������ �ȼ��� ���� 
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
	this->PlayerBulletCollisionEnemy(); //�÷��̾� �Ѿ˰� ���� �浹�� 
	this->PlayerCollisionEnemy(); //�÷��̾� ����� �ֳʹ� �浹�� 
	this->PlayerBoomCollisionBoom(); //�÷��̾� ����ź��  �ֳʹ� �浹�� 
	this->ChangeMap();
	
	//if (_fadein) 
	//{
	//	_fadecount++;
	//	if (_fadecount % 5 == 0) {
	//		_alpha -= 15;
	//		if (_alpha < 5) {
	//			_fadein = false;
	//			_alpha = 0;
	//		}
	//	}
	//}
	//if ( _fadeout)
	//{
	//	_fadecount++;
	//	if (_fadecount % 5 == 0) {
	//		_alpha += 15;
	//		if (_alpha > 240) {
	//			_alpha = 255;
	//		}
	//	}
	//}	
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
	//#################################�׽�Ʈ###############33
	RECT test = CAMERA->Relative(_testRect);
	Rectangle(getMemDC(), test);
	OBJECTMANAGER->Render();
	//_fade->alphaRender(getMemDC(), _alpha);
	
	
	//RECT _WALL = CAMERA->Relative(_wallRect);
	//Rectangle(getMemDC(), _WALL);
}

void StageOne::PlayerBulletCollisionEnemy()
{
	// _player _crab 
	RECT temp; 
	//############################################�ֳʹ� 2���� ��Ʈ���浹
	//#######################�Ϲ��Ѿ� 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;

		for (int j = 0; j < _crabCount; j++)
		{
			for (int k = 0; k < 4; ++k) {
				if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab[j]->getCol(k)))
				{
					_crab[j]->crab_damage(1);
					_player->playerbullet()->SetisFire(i, false);
					break;
				}
			}
		}
	}
	//###########################�غ�ӽŰ� �Ѿ� 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			for (int k = 0; k < 4; ++k) 
			{
				if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab[j]->getCol(k)))
				{
					_crab[j]->crab_damage(1);
					_player->heavybullet()->SetisFire(i, false);
					break;
				}
			}
		}
	}
}

void StageOne::PlayerCollisionEnemy()//�÷��̾� ����� �ֳʹ� ����� �浹������ 
{
	RECT temp;

	for (int i = 0; i < _crabCount; i++)
	{
		if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(2)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
		{//100 140������ũ�� �÷��̾� 
		 // Crab  left�ͺ� 
			cout << "�浹" << endl;
			_player->SetPosition({ (float)_crab[i]->getCol(2).left - 180, (float)_player->GetPosition().y });

		}
		else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(3)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
		{//100 140������ũ�� �÷��̾� 
		//Crab right�� �� 
			cout << "�浹" << endl;
			_player->SetPosition({ (float)_crab[i]->getCol(2).right + 170, (float)_player->GetPosition().y });
		}
		//���࿡ ũ���� ������ �÷��̾ �浹������ 
		else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab[i]->getCol(0)))
		{
			_player->SetJumppower(7.5f);

			//cout << "�浹" << endl; 
			//_player->
			if (!_player->GetIsleft())          //������Ʈ�� �浹�޴µ� ���� �����ʻ����Ͻ� 
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
		if (_player->playerboom()->getVBoom()[i].isFire == false)continue;

		for (int j = 0; j < _crabCount; j++)
		{
			if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab[j]->getCol(2)))
			{
				_crab[j]->crab_damage(1);
				_player->playerboom()->SetisFire(i, false);
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
				break;
			}
		}
	}


}

void StageOne::ChangeMap()
{
	if (_player->GetCollisionPlayer().right > _testRect.left &&
		_player->GetCollisionPlayer().left < _testRect.right &&
		_player->GetCollisionPlayer().top < _testRect.bottom)
	{
		if (KEYMANAGER->isToggleKey(VK_DOWN))
		{
			_fadeout = true;
			if ( _alpha > 240)
				SCENEMANAGER->ChangeScene("���Ͻ�������");
			
		}
	}
}

