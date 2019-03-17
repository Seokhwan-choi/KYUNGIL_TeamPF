#include "stdafx.h"
#include "BaseMent.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
HRESULT BaseMent::Init(void)
{
	SOUNDMANAGER->play("���Ͻ���");

	_player = new Player("�÷��̾�", { 406,633 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	//����� ����
	_fish = new Fish("Fish", { 1500 , WINSIZEY - 250 }, { 200,280 }, GameObject::Pivot::Center);
	_fish->Init();
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _fish);

	//��ǰ�� ��
	_bubbleCrabCount = 10;
	//��ǰ�� �ʱ�ȭ
	for (int i = 0; i < _bubbleCrabCount; i++)
	{
		string num = to_string(i);
		string name = "bubbleCrab" + num;

		if (i < 3)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 2500.f + (i * 100.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 3)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 3700.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 4)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 3900.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 4200.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 6)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 4500.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 7)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 5300.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 8)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 5600.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 9)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 6200.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}

		_bubbleCrab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab[i]);
	}

	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);
	
	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);


	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);
	//
	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);
	//

	OldMan* _oldman = new OldMan("oldman1", { 3000, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman);


	ItemUi* _item = new ItemUi("item", { WINSIZEX,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop, ITEM::FISH);
	OBJECTMANAGER->AddObject(ObjectType::UI, _item);

	//��ǰ�� ��
	_bubbleCrabCount = 10;
	//��ǰ�� �ʱ�ȭ
	for (int i = 0; i < _bubbleCrabCount; i++)
	{
		string num = to_string(i);
		string name = "bubbleCrab" + num;

		if (i < 3)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 2500.f + (i * 100.f), WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 3)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 3700.f, WINSIZEY / 2 + 175.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 4)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 3900.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 5)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 4200.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 6)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 4500.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 7)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 5300.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 8)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 5600.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}
		else if (i == 9)
		{
			_bubbleCrab[i] = new BubbleCrab(name, { 6200.f, WINSIZEY / 2 + 195.f }, { 100, 150 }, GameObject::Pivot::Center);
		}

		_bubbleCrab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab[i]);
	}

	//ū�� ��
	_bigCrabCount = 3;
	//ū�� �ʱ�ȭ
	for (int i = 0; i < _bigCrabCount; i++)
	{
		string num = to_string(i);
		string name = "bigCrab" + num;

		_bigCrab[i] = new BigCrab("bigCrab", { 3500.f + (i * 1000.f), WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
		_bigCrab[i]->Init();
		OBJECTMANAGER->AddObject(ObjectType::ENEMY, _bigCrab[i]);
	}

	_bgImage = IMAGEMANAGER->addImage("���Ϲ��", "BackGround/���Ϻ��̽�.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("���Ϲ���ȼ�", "BackGround/���Ϻ��̽��ȼ�.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("�볪��", "BackGround/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	CAMERA->SetWall(0);  //���� �ٲ���⋚���� �̱��� �����ڰ� �ʱ�ȭ�Ǿ��Ѵ� 
	_index = 0;	
	_count = 0;

	return S_OK;
}

void BaseMent::Release(void)
{
	OBJECTMANAGER->Release();
}

void BaseMent::Update(void)
{
	CAMERA->SetCamera2(_player->GetPosition());             //���� �ٲ� �̱��� �ʱ�ȭ�Ǽ� ���⼭ ī�޶�� �÷��̾�� ��´� 
	OBJECTMANAGER->Update();
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 21) 
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("�볪��")->setFrameX(_index);
		// �̹��� ������ ������ �����ϸ� ������ �ε��� ����
		if (_index == 21) 
		{
			_index--;
		}
	}

	if (_player->GetCollisionPlayer().left > 6600 ) 
	{
		SCENEMANAGER->ChangeScene("������������");
		SOUNDMANAGER->pause("���Ͻ���");

	}
	_player->BaseMentPixel();
	this->Collisison();
	this->FishColl();
}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### ���� ī�޶� ���� �ȵ���. ##############
	// =======================================================
	//����ǥ�� �������� �̷������� ���� 
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left -300, 0 -  CAMERA->GetCamera().top);// , 0 - CAMERA->GetCamera().top);
	_Out->frameRender(getMemDC(), 250 - CAMERA->GetCamera().left - 300, 390 - CAMERA->GetCamera().top);
	_pixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left - 300, 0 - CAMERA->GetCamera().top);
	char str[128]; 
	sprintf_s(str,"%d,%d", _ptMouse.x,_ptMouse.y);
	TextOut(getMemDC(),15,15,str,strlen(str));
	
	OBJECTMANAGER->Render();

	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}

void BaseMent::Collisison()
{
	RECT temp;

	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_bigCrab[j]->GetRect()))
			{
				_bigCrab[j]->bigCrab_damage(1);
				_player->playerbullet()->SetisFire(i, false);
				break;
			}
		}

	}


	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_bigCrab[j]->GetRect()))
			{
				_bigCrab[j]->bigCrab_damage(1);
				_player->heavybullet()->SetisFire(i, false);
				break;
			}
		}

	}


	for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_bigCrab[j]->GetRect()))
			{
				_bigCrab[j]->bigCrab_damage(1);
				_player->playerboom()->SetisFire(i, false);
				break;
			}
		}

	}

}

void BaseMent::FishColl()
{
	RECT temp;

	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (IntersectRect(&temp, &_fish->getCol(j), &_player->playerbullet()->getVBullet()[i].rc)
				&& _player->playerbullet()->getVBullet()[i].isFire == true)
			{
				_player->playerbullet()->SetisFire(i, false);
				_fish->fish_damage(j,1);
			}
		}
	}
}
