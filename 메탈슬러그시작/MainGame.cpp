#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "StageOne.h"
#include "StageTwo.h"
//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);


	StageOne* _stageone = new StageOne;
	SCENEMANAGER->AddScene("��������1", _stageone);
	SCENEMANAGER->ChangeScene("��������1");

	StageTwo* _stagetwo = new StageTwo;
	SCENEMANAGER->AddScene("��������2", _stagetwo);

	return S_OK;	
	//return S_OK�ؿ� �ڵ� ������ �ȵ�!!!!!!!!!!!
}

//==========================================================================//
//						## ���� ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->Release();
	//�̹��� Ŭ������ ���������� ����� �� ����.
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE();														
}

//==========================================================================//
//						## ������Ʈ ## update(void)							//
//==========================================================================//
void MainGame::update(void)
{
	gameNode::update();
	SCENEMANAGER->Update();
}

//==========================================================================//
//						## ���� ## render(HDC hdc)							//
//==========================================================================//
void MainGame::render()
{		
	//������ �������� (�̰� ������ �׳ɵα�)
	HDC memDC = this->getBackBuffer()->getMemDC();

	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//========================================================================//
	SCENEMANAGER->Render();
	
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}