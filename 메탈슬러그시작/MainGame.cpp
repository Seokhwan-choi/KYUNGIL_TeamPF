#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "startScene.h"
#include "choiceScene.h"
#include "stage1Scene.h"
//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	//_player = new Player("�÷��̾�", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	startScene* _startscene = new startScene;
	SCENEMANAGER->AddScene("����ȭ��", _startscene);
	SCENEMANAGER->ChangeScene("����ȭ��");

	choiceScene* _choicescene = new choiceScene;
	SCENEMANAGER->AddScene("ĳ���ͼ���ȭ��", _choicescene);

	//ù ����ȭ��
	stage1Scene* _stage1 = new stage1Scene;
	SCENEMANAGER->AddScene("��������1", _stage1);

	/*
	undergroundScene* _underground = new undergroundScene;
	SCENEMANAGER->AddScene("��������1_1", _underground);
	underriverScene&  _underriver = new underriverScene;
	SCENEMANAGER->AddScene("��������1_2", _underriver);
	boosScene&  _bossscene = new boosScene;
	SCENEMANAGER->AddScene("��������1_2", _bossscene);
	*/

	SCENEMANAGER->Init();
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
	//OBJECTMANAGER->Update();
	
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
	//OBJECTMANAGER->Render();
	
	SCENEMANAGER->Render();
	
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}