#include "stdafx.h"
#include "BaseMent.h"
#include "Player.h"
#include "Enemy.h"
HRESULT BaseMent::Init(void)
{
	_bgImage = IMAGEMANAGER->addImage("지하배경", "BackGround/지하베이스.bmp", 6774, 958);
	_pixelImage = IMAGEMANAGER->addImage("지하배경픽셀", "BackGround/지하베이스픽셀.bmo", 6774, 958);
	_Out = IMAGEMANAGER->addFrameImage("통나옴", "BackGround/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));

	_player = new Player("플레이어", { 406,633 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	//큰게 생성
	BigCrab* _bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
	//큰게 객체 추가하기
	_bigCrab->Init();
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, _bigCrab);


	CAMERA->SetWall(0);  //씬이 바뀌엇기떄문에 싱글톤 생성자가 초기화되야한다 
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
	
	OBJECTMANAGER->Render();

	//_Out->frameRender(getMemDC(), 500 - CAMERA->GetCamera().left, 500 - CAMERA->GetCamera().right);
}
