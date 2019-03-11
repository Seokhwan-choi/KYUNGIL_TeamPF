#include "stdafx.h"
#include "MainGame.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "startScene.h"
#include "choiceScene.h"
#include "stage1Scene.h"
//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	startScene* _startscene = new startScene;
	choiceScene* _choicescene = new choiceScene;
	stage1Scene* _stage1 = new stage1Scene;
	SCENEMANAGER->AddScene("����ȭ��", _startscene);
	SCENEMANAGER->AddScene("ĳ���ͼ���ȭ��", _choicescene);
	SCENEMANAGER->AddScene("�������� ��", new StageOne);

	//ù ����ȭ��
	//SCENEMANAGER->AddScene("��������1", _stage1);
	SCENEMANAGER->ChangeScene("����ȭ��");
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