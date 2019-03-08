#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
#include "BubbleCrab.h"
#include "Fish.h"
#include "BigCrab.h"


//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	SCENEMANAGER->AddScene("�������� ��", new StageOne);
	SCENEMANAGER->ChangeScene("�������� ��");

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	//���ڸ� ����
	//FlyBug* _flyBug = new FlyBug("flyBug", { WINSIZEX / 2 + 300, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//���ڸ� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _flyBug);

	//�� ����
	//Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175}, { 100, 150 }, GameObject::Pivot::Center);
	//�� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _crab);

	//��ǰ�� ����
	//BubbleCrab* _bubbleCrab = new BubbleCrab("bubbleCrab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//��ǰ�� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _bubbleCrab);

	//����� ����
	//Fish* fish = new Fish("fish", { WINSIZEX / 2 + 200,WINSIZEY / 2 + 200}, { 100,100 }, GameObject::Pivot::Center);
	//����� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, fish);

	//ū�� ����
	BigCrab* bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110}, { 200,280 }, GameObject::Pivot::Center);
	//ū�� ��ü �߰��ϱ�
	OBJECTMANAGER->AddObject(ObjectType::ENEMY, bigCrab);


	OBJECTMANAGER->Init();

	return S_OK;	
}

//==========================================================================//
//						## ���� ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->Release();
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
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================================//
	SCENEMANAGER->Render();
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}