#include "stdafx.h"
#include "BaseMent.h"
#include "Player.h"
#include "Enemy.h"
#include "timeUi.h"
#include "playerDataUi.h"
#include "oldMan.h"
#include "ItemUi.h"
HRESULT BaseMent::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("���Ϲ��", "BackGround/���Ϻ��̽�.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("���Ϲ���ȼ�", "BackGround/���Ϻ��̽��ȼ�.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("�볪��", "BackGround/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->play("���Ͻ���");


	_player = new Player("�÷��̾�", { 406,633 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	OldMan* _oldman = new OldMan("oldman1", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman);

	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	
	
	//OldMan* _oldman2 = new OldMan("oldman2", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::TIED, ITEM::HEAVY);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman2);

	

	//ū�� ����
	BigCrab* _bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
	//ū�� ��ü �߰��ϱ�
	_bigCrab->Init();
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, _bigCrab);
	//������
	ItemUi* _item = new ItemUi("item", { WINSIZEX * 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop, ITEM::FISH);
	OBJECTMANAGER->AddObject(ObjectType::UI, _item);
	//�÷��̾� ���� ������ 
	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	timeUi* _timeui2 = new timeUi("timeui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui2);

	OldMan* _oldman3 = new OldMan("oldman3", { WINSIZEX*3, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman3);


	CAMERA->SetWall(0);  //���� �ٲ���⋚���� �̱��� �����ڰ� �ʱ�ȭ�Ǿ��Ѵ� 
	_index = 0;	
	_count = 0;
	_check = false;

	return S_OK;
}

void BaseMent::Release(void)
{
	OBJECTMANAGER->Release();
}

void BaseMent::Update(void)
{
	//����
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

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		_check = !_check;
	}
	

	//#################################�������� ��ȯ##################3
	if (_player->GetCollisionPlayer().right > 6000 )

	{
		
		SCENEMANAGER->ChangeScene("������������");
		
	}

}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### ���� ī�޶� ���� �ȵ���. ##############
	// =======================================================
	//����ǥ�� �������� �̷������� ���� 
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left -300, 0 -  CAMERA->GetCamera().top);// , 0 - CAMERA->GetCamera().top);
	_Out->frameRender(getMemDC(), 250 - CAMERA->GetCamera().left - 300, 390 - CAMERA->GetCamera().top);
	
	char str[128]; 
	sprintf_s(str,"%d,%d", _ptMouse.x,_ptMouse.y);
	TextOut(getMemDC(),15,15,str,strlen(str));

	if (!_check) {
		_pixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left - 300, 0 - CAMERA->GetCamera().top);
	}
	
	OBJECTMANAGER->Render();

	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}

