#include "stdafx.h"
#include "BaseMent.h"
#include "Player.h"
#include "Enemy.h"

HRESULT BaseMent::Init(void)
{
	
	_player = new Player("플레이어", { 1560,WINSIZEY / 2 + 175 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	//큰게 생성
	BigCrab* _bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
	//큰게 객체 추가하기
	_bigCrab->Init();
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, _bigCrab);

	
	
	_bgImage = IMAGEMANAGER->addImage("지하배경", "BackGround/지하베이스.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("지하배경픽셀", "BackGround/지하베이스픽셀.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("통나옴", "BackGround/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));


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
	OBJECTMANAGER->Update();
	CAMERA->SetCamera(_player->GetPosition());
	_count++;
	if (_count % 5 == 0) {
		_index++;
		if (_index > 21) 
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("통나옴")->setFrameX(_index);
		// 이미지 마지막 프레임 도달하면 프레임 인덱스 고정
		if (_index == 21) {
			_index--;
		}
	}
}

void BaseMent::Render(void)
{
	// =======================================================
	// ############### 아직 카메라 보정 안들어갔다. ##############
	// =======================================================
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -310 - CAMERA->GetCamera().top);
	_Out->frameRender(getMemDC(), 250 - CAMERA->GetCamera().left, 390 - CAMERA->GetCamera().top);

	OBJECTMANAGER->Render();
	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}
