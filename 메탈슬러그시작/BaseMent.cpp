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
	_bgImage = IMAGEMANAGER->addImage("지하배경", "BackGround/지하베이스.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("지하배경픽셀", "BackGround/지하베이스픽셀.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("통나옴", "BackGround/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->play("지하시작");


	_player = new Player("플레이어", { 406,633 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	OldMan* _oldman = new OldMan("oldman1", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman);

	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	
	
	//OldMan* _oldman2 = new OldMan("oldman2", { 1500, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::TIED, ITEM::HEAVY);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman2);

	

	//큰게 생성
	BigCrab* _bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
	//큰게 객체 추가하기
	_bigCrab->Init();
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, _bigCrab);
	//아이템
	ItemUi* _item = new ItemUi("item", { WINSIZEX * 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop, ITEM::FISH);
	OBJECTMANAGER->AddObject(ObjectType::UI, _item);
	//플레이어 관련 데이터 
	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	timeUi* _timeui2 = new timeUi("timeui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui2);

	OldMan* _oldman3 = new OldMan("oldman3", { WINSIZEX*3, WINSIZEY / 2 }, { 150,150 }, GameObject::Pivot::LeftTop, CAPTIVE::MOVE, ITEM::HEAVY);
	OBJECTMANAGER->AddObject(ObjectType::Enum::UI, _oldman3);


	CAMERA->SetWall(0);  //씬이 바뀌엇기떄문에 싱글톤 생성자가 초기화되야한다 
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
	//사운드
	CAMERA->SetCamera2(_player->GetPosition());             //씬이 바뀌어서 싱글톤 초기화되서 여기서 카메라는 플레이어로 잡는다 
	OBJECTMANAGER->Update();
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 21) 
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("통나옴")->setFrameX(_index);
		// 이미지 마지막 프레임 도달하면 프레임 인덱스 고정
		if (_index == 21) 
		{
			_index--;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		_check = !_check;
	}
	

	//#################################씬보스로 전환##################3
	if (_player->GetCollisionPlayer().right > 6000 )

	{
		
		SCENEMANAGER->ChangeScene("보스스테이지");
		
	}

}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### 아직 카메라 보정 안들어갔다. ##############
	// =======================================================
	//두좌표만 잇을때는 이런식으로 쓴다 
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

