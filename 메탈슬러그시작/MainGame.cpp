#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"

//==========================================================================//
//						## �ʱ�ȭ ## init(void)								//
//==========================================================================//
HRESULT MainGame::init(void)
{
	gameNode::init(true); 

	//Monster* monster = new Monster("Monster", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::Center);
	//OBJECTMANAGER->AddObject(ObjectType::Object, monster);

	_player = new Player("�÷��̾�", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _player);


	return S_OK;	
	//return S_OK�ؿ� �ڵ� ������ �ȵ�!!!!!!!!!!!
}

//==========================================================================//
//						## ���� ## release(void)								//
//==========================================================================//
void MainGame::release(void)
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����.
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE();		
	

}

//==========================================================================//
//						## ������Ʈ ## update(void)							//
//==========================================================================//
void MainGame::update(void)
{
	gameNode::update();

	OBJECTMANAGER->Update();
	
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
	OBJECTMANAGER->Render();

	
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());

}