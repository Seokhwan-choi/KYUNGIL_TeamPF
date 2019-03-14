#include "stdafx.h"
#include "MainGame.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "startScene.h"
#include "choiceScene.h"
#include "BaseMent.h"
#include "BossStage.h"
#include "LoadingScene.h"

//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 
	
	SCENEMANAGER->AddScene("����ȭ��", new startScene);
	SCENEMANAGER->AddScene("ĳ���ͼ���ȭ��", new choiceScene);
	SCENEMANAGER->AddScene("����������", new StageOne);
	SCENEMANAGER->AddScene("���Ͻ�������", new BaseMent);
	SCENEMANAGER->AddScene("������������", new BossStage);
	SCENEMANAGER->AddScene("�ε�", new LoadingScene);
	//ù ����ȭ��
	SCENEMANAGER->ChangeScene("����������");
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
	SCENEMANAGER->Render();
	//OBJECTMANAGER->Render();

	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}