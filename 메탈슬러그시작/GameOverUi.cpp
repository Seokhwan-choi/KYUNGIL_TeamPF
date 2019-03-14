#include "stdafx.h"
#include "GameOverUi.h"
#include "GameOverUi_2.h"
#include "timeUi.h"
//========================================================
// ���ӿ����� ui( size : 1280x960 )
//========================================================
GameOverUi::GameOverUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_size = size;
	_pivot = Pivot::LeftTop;

	//========================================================
	//��Ʈ �ʱ�ȭ 
	//========================================================
	//�߾� ���� �� ���� �̹��� ��Ʈ
	numberRc = RectMake(570, 444, 141, 208);
	continueRc = RectMake(400,307,435,70);
	//���� ��Ƽ�� �� ���� �̹��� ��Ʈ
	topcontinueRc = RectMake(208, 32, 229, 71);
	topnumberRc = RectMake(440, 23, 28, 69);
	//========================================================
	//�̹��� �ʱ�ȭ 
	//========================================================
	//�߾� ��Ƽ�� �̹���
	_continueImage = IMAGEMANAGER->findImage("continue");
	_numberImage = IMAGEMANAGER->findImage("number");
	_gameOverImage = IMAGEMANAGER->findImage("gameover");
	
	//========================================================
	//�̹��� ���� int�� ����
	//========================================================
	_number = 9;
	_count = 0;
	_index = 0;
	_isShow = false;
}

GameOverUi::~GameOverUi()
{
}

HRESULT GameOverUi::Init()
{
	return S_OK;
}

void GameOverUi::Release()
{
}

void GameOverUi::Update()
{
	
}

void GameOverUi::Render()
{
	//Ʈ���϶��� ������
	if (_isShow == true) {
		_numberImage->frameRender(getMemDC(), numberRc.left, numberRc.top, _number, 0);
		_continueImage->render(getMemDC(), continueRc.left, continueRc.top);
		_continueImage->stretchRender(getMemDC(), topcontinueRc.left, topcontinueRc.top, 0.3f);
		_numberImage->stretchFrameRender(getMemDC(), topnumberRc.left, topnumberRc.top, _number, 0, 0.2f);
	}

}

void GameOverUi::gameOver()
{
	_count++;
	if (_count % 100 == 0) {
		_number--;
	}
	if (_number <= 0) {
		//Ÿ�� ������ ������
		((timeUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "timeui"))->setIsShow(false);
		
		((GameOverUi_2*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui2"))->setIsShow(true);
		((GameOverUi_2*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui2"))->gameOver();
	}
}
