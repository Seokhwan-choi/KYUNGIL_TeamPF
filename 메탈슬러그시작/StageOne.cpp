#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "playerDataUi.h"
#include "OldMan.h"
#include "GameCompleteUi.h"
#include "ItemUi.h"
#include "totalScore.h"

HRESULT StageOne::Init(void)
{
	_player = new Player("�÷��̾�", { 400,0 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);
		
	_crab = new Crab("crab", { 2060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	_crab->Init();
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab);
	//_boss = new BubbleCrab("boss", { 2060, WINSIZEY / 2 + 175 }, { 100,150 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _boss);
	//_boss->Init();

	
	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);
	//
	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);
	//
	//stage1StartUi* _stage1startui = new stage1StartUi("stage1startui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _stage1startui);
	//
	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);
	//
	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	//GameCompleteUi* _gamecompleteui = new GameCompleteUi("gamecompleteui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _gamecompleteui);


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
	_bgImage = IMAGEMANAGER->addImage("���", "Background/���.bmp", 14070, 1150, true , RGB(255,0,255));
	_bgSea = IMAGEMANAGER->addFrameImage("����ⷷ", "Background/����ⷷ2.bmp", 19568, 278, 8, 1);
	_wallImage = IMAGEMANAGER->addFrameImage("���庮", "Background/���庮.bmp", 5400, 960, 6, 1, true, RGB(255, 0, 255));
	_bgImage2 = IMAGEMANAGER->addImage("����ǹ��", "Background/����ǹ��.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_PixelImage = IMAGEMANAGER->addImage("����ȼ�", "Background/����ȼ�.bmp", 14070, 1150, true, RGB(255, 0, 255));
	_tongImage = IMAGEMANAGER->addFrameImage("��", "Background/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	_PixelCheck = false;

	_wallRect = RectMakeCenter(6750, WINSIZEY/2, 50, 1500);

	_index = 0;
	_count = 0;

	_index2 = 0;
	_count2 = 0;

	_index3 = 0;
	_count3 = 0;

	_crush = false;

	return S_OK;
}

void StageOne::Release(void)
{
	OBJECTMANAGER->Release();
}

void StageOne::Update(void)
{
	OBJECTMANAGER->Update();

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

	CAMERA->SetCamera(_player->GetPosition());

	if (_crush) {
		RECT _temp;
		if (IntersectRect(&_temp, &_player->GetRect(), &_wallRect)) {
			_player->SetPosition({
				_wallRect.left - (_player->GetSize().x / 2.0f),
				_player->GetPosition().y });
		}
		CAMERA->SetCamera(_player->GetPosition());
	}
	this->PlayerBulletCollisionEnemy(); //�÷��̾� �Ѿ˰� ���� �浹�� 
	this->PlayerCollisionEnemy(); //�÷��̾� ����� �ֳʹ� �浹�� 
	this->PlayerBoomCollisionBoom(); //�÷��̾� ����ź��  �ֳʹ� �浹�� 
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
	
	OBJECTMANAGER->Render();
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
		if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab->getCol(2)  ))
		{
			_crab->Damage(1);
			_player->playerbullet()->getVBullet()[i].isFire = false;
			break; 
		}
	}
	//###########################�غ�ӽŰ� �Ѿ� 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;
		if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab->getCol(2)))
		{
			_crab->Damage(1);
			_player->heavybullet()->getVBullet()[i].isFire = false; 
			break; 
		}
	}
	

	//############################################�ֳʹ� 1���� ��Ʈ���浹
	//#######################�Ϲ��Ѿ� 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;
		if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab->getCol(1)))
		{
			_crab->Damage(1);
			_player->playerbullet()->getVBullet()[i].isFire = false;
			break;
		}
	}
	//###########################�غ�ӽŰ� �Ѿ� 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;
		if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab->getCol(1)))
		{
			_crab->Damage(1);
			_player->heavybullet()->getVBullet()[i].isFire = false;
			break;
		}
	}


	//############################################�ֳʹ� 3���� ��Ʈ���浹
	//#######################�Ϲ��Ѿ� 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;
		if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab->getCol(3)))
		{
			_crab->Damage(1);
			_player->playerbullet()->getVBullet()[i].isFire = false;
			break;
		}
	}
	//###########################�غ�ӽŰ� �Ѿ� 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;
		if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab->getCol(3)))
		{
			_crab->Damage(1);
			_player->heavybullet()->getVBullet()[i].isFire = false;
			break;
		}
	}



	//############################################�ֳʹ� 4���� ��Ʈ���浹
	//#######################�Ϲ��Ѿ� 
	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;
		if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab->getCol(4)))
		{
			_crab->Damage(1);
			_player->playerbullet()->getVBullet()[i].isFire = false;
			break;
		}
	}
	//###########################�غ�ӽŰ� �Ѿ� 
	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;
		if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab->getCol(4)))
		{
			_crab->Damage(1);
			_player->heavybullet()->getVBullet()[i].isFire = false;
			break;
		}
	}


}

void StageOne::PlayerCollisionEnemy()//�÷��̾� ����� �ֳʹ� ����� �浹������ 
{
	RECT temp; 
	if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab->getCol(2)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
	{//100 140������ũ�� �÷��̾� 
	 // Crab  left�ͺ� 
		cout << "�浹" << endl;
		_player->SetPosition({ (float)_crab->getCol(2).left - 180, (float)_player->GetPosition().y } );
	
	}
	else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab->getCol(3)))// && _player->GetCollisionPlayer().right <=_crab->getCol(2).left )
	{//100 140������ũ�� �÷��̾� 
	//Crab right�� �� 
		cout << "�浹" << endl;
		_player->SetPosition({ (float)_crab->getCol(2).right + 170, (float)_player->GetPosition().y });
	}
	//���࿡ ũ���� ������ �÷��̾ �浹������ 
	else if (IntersectRect(&temp, &_player->GetCollisionPlayer(), &_crab->getCol(0)))
	{
		_player->SetJumppower(7.5f);

		//cout << "�浹" << endl; 
		//_player->
		if (!_player->GetIsleft())          //������Ʈ�� �浹�޴µ� ���� �����ʻ����Ͻ� 
		{
			_player->SetPosition({ (float)_player->GetPosition().x - 10,(float)_player->GetPosition().y - 10 });
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
		if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab->getCol(2)))
		{
			_crab->Damage(1);
			_player->playerboom()->SetisFire(i, false);
			cout << "����" << endl;
			cout << &_player->playerboom()->getVBoom()[i].rc.right << endl;
			break;
		}
	}
	for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	{
		if (_player->playerboom()->getVBoom()[i].isFire == false) continue;
		if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_crab->getCol(3))) 
		{
			_crab->Damage(1);
			_player->playerboom()->SetisFire(i, false);
			cout << &_player->playerboom()->getVBoom()[i].rc.right << endl;
			break;
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
	//	//	cout << "�浹" << endl;
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

