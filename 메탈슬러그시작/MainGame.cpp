#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
#include "BubbleCrab.h"
#include "Fish.h"
#include "BigCrab.h"
#include "startScene.h"
#include "choiceScene.h"
#include "stage1Scene.h"
#include "Monster.h"
//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 
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
	//BigCrab* bigCrab = new BigCrab("bigCrab", { 500 ,WINSIZEY / 2 + 110}, { 200,280 }, GameObject::Pivot::Center);

	//ū�� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::ENEMY, bigCrab);


	//OBJECTMANAGER->Init();
	//_player = new Player("�÷��̾�", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);
	//_monster = new Monster("����", { WINSIZEX / 2 + 200,WINSIZEY / 2 }, { 100,100 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _monster);

	SCENEMANAGER->AddScene("�������� ��", new StageOne);

	startScene* _startscene = new startScene;
	SCENEMANAGER->AddScene("����ȭ��", _startscene);

	choiceScene* _choicescene = new choiceScene;
	SCENEMANAGER->AddScene("ĳ���ͼ���ȭ��", _choicescene);

	stage1Scene* _stage1 = new stage1Scene;
	SCENEMANAGER->AddScene("��������1", _stage1);

	//ù ����ȭ��
	SCENEMANAGER->ChangeScene("�������� ��");

	

	

	/*
	undergroundScene* _underground = new undergroundScene;
	SCENEMANAGER->AddScene("��������1_1", _underground);
	underriverScene&  _underriver = new underriverScene;
	SCENEMANAGER->AddScene("��������1_2", _underriver);
	boosScene&  _bossscene = new boosScene;
	SCENEMANAGER->AddScene("��������1_2", _bossscene);
	*/

	return S_OK;	
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
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================================//
	SCENEMANAGER->Render();
	//OBJECTMANAGER->Render();

	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}