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
	_center = { 30,30 };
	//체력 200으로 설정해둠 200으로 업데이트에 맞았을떄 - 해줘야함
	_hpRc = RectMake(64, 75, 200, 19);
	//구한생명수 렉트
	for (int i = 0; i < 10; i++) {
		_saveRc[i] = RectMake(68+_center.x *i , 888, _center.x,_center.y);
		_isShow[i] = false;
	}
	_bombarmsImg = IMAGEMANAGER->addImage("bombarms", "UI/PlayerStateRegardingPicture/armsbomb.bmp", 261, 72, true, RGB(255, 0, 255));
	_guageImg = IMAGEMANAGER->addImage("guagebar", "UI/PlayerStateRegardingPicture/guageBar.bmp", 222, 35, true, RGB(255, 0, 255));
	_1upImg = IMAGEMANAGER->addImage("1up", "UI/PlayerStateRegardingPicture/1up=.bmp", 123, 36, true, RGB(255, 0, 255));
	_infiniteImg = IMAGEMANAGER->addImage("infinite", "UI/infinite.bmp", 80, 30, true, RGB(255, 0, 255));

	_lifeImg = IMAGEMANAGER->addFrameImage("lifescore", "UI/playerlife.bmp", 380, 36, 10, 1, true, RGB(255, 0, 255));
	_scoreImg = IMAGEMANAGER->addFrameImage("score", "UI/PlayerStateRegardingPicture/점수 숫자.bmp", 340, 34, 10, 1, true, RGB(255, 0, 255));
	_bombImg = IMAGEMANAGER->addFrameImage("bombscore", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));
	_armsImg = IMAGEMANAGER->addFrameImage("armsImg", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스체력바", "UI/bossbar.bmp", 201,19);
	IMAGEMANAGER->addImage("만세", "UI/save.bmp", 30, 30, true, RGB(255, 0, 255));

	//불변수 초기화
	_isMeet = false;	//만나지 않았다
	_count = 0;
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
	_count++;
	if (DATA->getLife() <= 0) {
		//캐릭터  종료씬 update부분 넣어준다.
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->setIsShow(true);
		((GameOverUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gameoverui"))->gameOver();
	}

	//this->setRect({300,WINSIZEY/2.f});
	
}

void playerDataUi::Render()
{

	//프레임 이미지들
	//점수 처리 표기 처리
	//10보다 작을때
	if (DATA->getScore() < 10) {
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore(), 0);
	}
	//백자리
	if (DATA->getScore() >= 100 && DATA->getScore() < 1000) {
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() - DATA->getScore() % 100) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() / 10) % 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//천자리
	if (DATA->getScore() >= 1000 && DATA->getScore() < 10000) {
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() - DATA->getScore() % 1000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//만자리
	if (DATA->getScore() >= 10000 && DATA->getScore() < 100000) {
		_scoreImg->frameRender(getMemDC(), 168, 34, (DATA->getScore() - DATA->getScore() % 10000) / 10000, 0);
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() % 10000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//십만자리
	if (DATA->getScore() >= 100000 && DATA->getScore() < 1000000) {
		_scoreImg->frameRender(getMemDC(), 143, 34, (DATA->getScore() - DATA->getScore() % 100000) / 100000, 0);
		_scoreImg->frameRender(getMemDC(), 168, 34, (DATA->getScore() % 100000) / 10000, 0);
		_scoreImg->frameRender(getMemDC(), 193, 34, (DATA->getScore() % 10000) / 1000, 0);
		_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() % 1000) / 100, 0);
		_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() % 100) / 10, 0);
		_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);
	}
	//생명
	if (DATA->getLife() < 10) {
		_lifeImg->frameRender(getMemDC(), 201, 102, DATA->getLife(), 0);
	}
	//무한숫자 
	if (DATA->getWeapon() == WEAPON::NORMAL) {
		_infiniteImg->render(getMemDC(), 343, 67);
	}
	if (DATA->getWeapon() == WEAPON::HEAVY) {
		//총알 갯수
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
	//수류탄수
	if (DATA->getBomb() < 10) {
		_bombImg->frameRender(getMemDC(), 504, 67, DATA->getBomb(), 0);
	}
	if (DATA->getBomb() >= 10) {
		_bombImg->frameRender(getMemDC(), 466, 67, (DATA->getBomb() - DATA->getBomb() % 10) / 10, 0);
		_bombImg->frameRender(getMemDC(), 500, 67, DATA->getBomb() % 10, 0);
	}
	//변하지 않는 이미지
	_bombarmsImg->render(getMemDC(), _bombArmsRc.left, _bombArmsRc.top);
	_guageImg->render(getMemDC(), _guageRc.left, _guageRc.top);
	_1upImg->render(getMemDC(), _upRc.left, _upRc.top);
	//구한 포로수 숫자 만들기
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		for (int i = 0; i < DATA->getCaptive(); i++) {
			Rectangle(getMemDC(), _saveRc[i]);
		}
	}

	if (DATA->getCaptive() > 0) {
		for (int i = 0; i < DATA->getCaptive(); i++) {
			if (_isShow[i] == false) {
				IMAGEMANAGER->render("만세", getMemDC(), _saveRc[i].left, _saveRc[i].top);
			}
		}
	}

	//보스를 만났다
	if (_isMeet == true ) {
		IMAGEMANAGER->render("보스체력바", getMemDC(),_hpRc.left, _hpRc.top);
	}
}



void playerDataUi::setRect(POINTFLOAT center)
{
	float _speed = 8.f;	
	for (int i = 0; i < DATA->getCaptive(); i++) {
		if (_isShow[i] == false) {
			float _angle = GetAngle(_saveRc[i].left, _saveRc[i].top, center.x, center.y);
			_saveRc[i].left += cosf(_angle) * _speed - i;
			_saveRc[i].right += cosf(_angle) * _speed - i;
			_saveRc[i].bottom -= sinf(_angle) * _speed - i;
			_saveRc[i].top -= sinf(_angle) * _speed - i;

			if (_saveRc[i].top < center.y + 20) {
				_isShow[i] = true;
				break;
			}
		}
	}
}

