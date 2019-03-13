#include "stdafx.h"
#include "playerDataUi.h"
#include "Player.h"
#include "GameOverUi.h"

playerDataUi::playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_bombArmsRc = RectMake(306, 33, 197, 75);
	_upRc = RectMake(73, 101, 123, 36);
	_guageRc = RectMake(56, 67, 222, 35);
	_score = RectMake(400, 40, 25, 33);
	_bombarmsImg = IMAGEMANAGER->addImage("bombarms", "UI/PlayerStateRegardingPicture/armsbomb.bmp", 261, 72, true, RGB(255, 0, 255));
	_guageImg = IMAGEMANAGER->addImage("guagebar", "UI/PlayerStateRegardingPicture/guageBar.bmp", 222, 35, true, RGB(255, 0, 255));
	_1upImg = IMAGEMANAGER->addImage("1up", "UI/PlayerStateRegardingPicture/1up=.bmp", 123, 36, true, RGB(255, 0, 255));
	_infiniteImg = IMAGEMANAGER->addImage("infinite", "UI/infinite.bmp", 80, 30, true, RGB(255, 0, 255));

	_lifeImg = IMAGEMANAGER->addFrameImage("lifescore", "UI/playerlife.bmp", 380, 36, 10, 1, true, RGB(255, 0, 255));
	_scoreImg = IMAGEMANAGER->addFrameImage("score", "UI/PlayerStateRegardingPicture/���� ����.bmp", 340, 34, 10, 1, true, RGB(255, 0, 255));
	_bombImg = IMAGEMANAGER->addFrameImage("bombscore", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));
	_armsImg = IMAGEMANAGER->addFrameImage("armsImg", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("����", "UI/save.bmp", 35, 36, true, RGB(255, 0, 255));

	DATA->Init();
}

playerDataUi::~playerDataUi()
{
}

HRESULT playerDataUi::Init()
{
	return S_OK;
}

void playerDataUi::Release()
{
}

void playerDataUi::Update()
{
	if (DATA->getLife() <= 0) {
		//ĳ����  ����� update�κ� �־��ش�.
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->setIsShow(true);
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->gameOver();
	}
	
}

void playerDataUi::Render()
{

	//������ �̹�����
	//���� ó�� ǥ�� ó��
	//10���� ������
	if (DATA->getScore() < 10) {
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore(), 0);
	}
	//���ڸ�
	if (DATA->getScore() >= 100 && DATA->getScore() < 1000) {
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() - DATA->getScore() % 100) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() / 10) % 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//õ�ڸ�
	if (DATA->getScore() >= 1000 && DATA->getScore() < 10000) {
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() - DATA->getScore() % 1000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//���ڸ�
	if (DATA->getScore() >= 10000 && DATA->getScore() < 100000) {
		_scoreImg->frameRender(getMemDC(), 168, 34, (DATA->getScore() - DATA->getScore() % 10000) / 10000, 0);
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() % 10000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//�ʸ��ڸ�
	if (DATA->getScore() >= 100000 && DATA->getScore() < 1000000) {
		_scoreImg->frameRender(getMemDC(), 143, 34, (DATA->getScore() - DATA->getScore() % 100000) / 100000, 0);
		_scoreImg->frameRender(getMemDC(), 168, 34, (DATA->getScore() % 100000) / 10000, 0);
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() % 10000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//����
	if (DATA->getLife() < 10) {
		_lifeImg->frameRender(getMemDC(), 201, 102, DATA->getLife(), 0);
	}
	//���Ѽ��� 
	if (DATA->getWeapon() == WEAPON::NORMAL) {
		_infiniteImg->render(getMemDC(), 343, 67);
	}
	if (DATA->getWeapon() == WEAPON::HEAVY) {
		//�Ѿ� ����
		if (DATA->getArms() < 10) {
			_armsImg->frameRender(getMemDC(), 406, 67, DATA->getArms(), 0);
		}
		if (DATA->getArms() >= 10 && DATA->getArms() < 100) {
			_armsImg->frameRender(getMemDC(), 368, 67, (DATA->getArms() - DATA->getArms() % 10) / 10, 0);
			_armsImg->frameRender(getMemDC(), 409, 67, DATA->getArms() % 10, 0);
		}
		if (DATA->getArms() >= 100 && DATA->getArms() < 1000) {
			_armsImg->frameRender(getMemDC(), 330, 67, (DATA->getArms() - DATA->getArms() % 100) / 100, 0);
			_armsImg->frameRender(getMemDC(), 368, 67, (DATA->getArms() / 10) % 10, 0);
			_armsImg->frameRender(getMemDC(), 406, 67, DATA->getArms() % 10, 0);
		}
	}
	//����ź��
	if (DATA->getBomb() < 10) {
		_bombImg->frameRender(getMemDC(), 504, 67, DATA->getBomb(), 0);
	}
	if (DATA->getBomb() >= 10) {
		_bombImg->frameRender(getMemDC(), 466, 67, (DATA->getBomb() - DATA->getBomb() % 10) / 10, 0);
		_bombImg->frameRender(getMemDC(), 500, 67, DATA->getBomb() % 10, 0);
	}
	//������ �ʴ� �̹���
	_bombarmsImg->render(getMemDC(), _bombArmsRc.left, _bombArmsRc.top);
	_guageImg->render(getMemDC(), _guageRc.left, _guageRc.top);
	_1upImg->render(getMemDC(), _upRc.left, _upRc.top);
	
}
