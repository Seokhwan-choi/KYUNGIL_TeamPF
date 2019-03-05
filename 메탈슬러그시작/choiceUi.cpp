#include "stdafx.h"
#include "choiceUi.h"



choiceUi::choiceUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_size = size;
	_pivot = Pivot::LeftTop;
	
	_isShow = false;															//ĳ���ͼ����Ͽ� �����ٰ��ΰ�?
	//========================================================
	//��Ʈ �ʱ�ȭ 
	//========================================================
	for (int i = 0; i < 4; i++) {
		gameStartRc[i] = RectMake(76 +286 * i, 309, 286, 535);	//4�� ��Ʈ ��ġ(���� ��Ʈ)
	}
	//��� ��Ʈ �������ֱ�
	characterRc[0] = RectMake(76, 309, 269, 535); //ĳ���� ���� 4�� ��Ʈ ��ġ
	characterRc[1] = RectMake(362, 309, 269, 535);
	characterRc[2] = RectMake(648, 309, 269, 535);
	characterRc[3] = RectMake(935, 309, 269, 535);
	//������ �ö󰡴� �� ������ֱ�
	door[0] = RectMake(76,309,269, 535);
	door[3] = RectMake(362, 309, 269, 535);
	door[2] = RectMake(648, 309, 269, 535);
	door[1] = RectMake(935, 309, 269, 535);

	//========================================================
	// bool �ʱ�ȭ
	//========================================================

	for (int i = 0; i < 4; i++) {
		_isCheck[i] = false;													//ĳ���� �����ֱ����� �Ұ� �ʱ�ȭ
		_goUp[i] = false;														//������ ĳ���� �����ֱ� ���� �� ��Ʈ �ø��� ���� �Ұ�
	}
	_doorUp = false;
	//========================================================
	// ������ ��Ʈ �ʱ�ȭ
	//========================================================
	_position = { 219,422 };
	gameStartRc[4] = RectMake(_position.x, _position.y, 30, 30);					//������ ��Ʈ �ʱ�ȭ
	
	//========================================================
	// true ���� �ε��� ���� ���� �ʱ�ȭ
	//========================================================
	_a = 0;																		//Ư�� true�� ���� �ε����� ��� ���� �ʱ�ȭ
	
	//========================================================
	// �ð� ���� ���� �ʱ�ȭ
	//========================================================
	_count = 0;																	
	_time = 30;																	//���ѽð� �ʱ�ȭ
	//========================================================
	// �̹��� ���� ���� �ʱ�ȭ
	//========================================================
	_background = IMAGEMANAGER->addImage("choiceimage", "image/character_main.bmp", 1280, 960, true, RGB(255,0,255));
	_timeImage = IMAGEMANAGER->addFrameImage("timenumber", "image/scoreNumber.bmp", 500, 48, 10, 1, true, RGB(0, 248, 0));
	_doorImage = IMAGEMANAGER->addImage("door", "image/door.bmp", 271, 535, true, RGB(255, 0, 255));
	
	//ĳ���� ���� ���� �ʾ��� ��  ������ �̹��� ����
	_characterImage[0] = IMAGEMANAGER->addImage("characterblack1", "image/marco_black.bmp", 271, 535);
	_characterImage[1] = IMAGEMANAGER->addImage("characterblack2", "image/eri_black.bmp", 271, 535);
	_characterImage[2] = IMAGEMANAGER->addImage("characterblack3", "image/tarma_black.bmp", 271, 535);
	_characterImage[3] = IMAGEMANAGER->addImage("characterblack4", "image/pio_black.bmp", 271, 535);


}	

choiceUi::~choiceUi()
{
}

HRESULT choiceUi::Init()
{
	return S_OK;
}

void choiceUi::Release()
{
}

void choiceUi::Update()
{
	_count++;
	//1�ʿ� 1�� �����ϵ��� ����� �ش� 
	if (_count % 100 == 0) {
		_time--;
	}
	//0.5
	if (_count == 50) {
		_doorUp = true;
	}
	if (_doorUp == true) {
		for (int i = 0; i < 4; i++) {
			door[i].bottom -= 7 * i + 10;
			door[i].top -= 7 * i + 10;
		}
	}
	//������ ������ ���� ��Ʈ ������ ����� �ʰԲ� ���� ��������
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) &&
		(gameStartRc[4].right <1019)) {
		gameStartRc[4].left += 268;
		gameStartRc[4].right += 268;
	}
	//���� ������ ���� ��Ʈ  ������ ����� �ʰԲ� ���� ��������
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) &&
		(gameStartRc[4].left > 268)) {
		gameStartRc[4].left -= 268;
		gameStartRc[4].right -= 268;
	}
	//���� ������ �ö� ��Ʈ �������ֱ�
	//������ ��Ʈ i�� _a�� �־��ش�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		for (int i = 0; i < 4; i++) {
			if (_isCheck[i] == true) {
				gameStartRc[i].bottom -= 10;
				gameStartRc[i].top -= 10;
				_a = i;
				_goUp[_a] = true;
			}
		}
	}
	//�ð��� 0���� �Ǹ� �ڵ����� ĳ���� ���� �ǵ��� ����
	if (_time == 0) {
		for (int i = 0; i < 4; i++) {
			if (_isCheck[i] == true) {
				gameStartRc[i].bottom -= 10;
				gameStartRc[i].top -= 10;
				_a = i;
				_goUp[_a] = true;
			}
		}
	}
	//������ ��Ʈ�� �÷��� �ȿ� �ִ� ĳ���͸� �����ش�
	if (_goUp[_a] == true) {
		gameStartRc[_a].bottom -= 10;
		gameStartRc[_a].top -= 10;
		gameStartRc[4].bottom -= WINSIZEX;
		gameStartRc[4].top -= WINSIZEY;
		_isShow = true;
	}
	//������ ��Ʈ�� �ø��� 5�ʵ� ���� �ٲ��ش�
	if (_isShow == true) {
		if (_time == 500) {
			//SCENEMANAGER->ChangeScene("�� ����")
		}
	}

	this->UpdateRectByPivot();	// RECT �׷��ش�.

}

void choiceUi::Render()
{
	if (_doorUp == true){
		for (int i = 0; i < 4; i++) {
			_characterImage[i]->render(getMemDC(), characterRc[i].left, characterRc[i].top);
		}
	}
	//���ö󰡵��� �ϴ°�
	for (int i = 0; i < 4; i++)
	{
		_doorImage->render(getMemDC(), door[i].left, door[i].top);
	}
	//����ȭ�� â �����ֱ�
	_background->render(getMemDC(), 0, 0);

	//���ѽð� ǥ��
	if (_time < 10) _timeImage->frameRender(getMemDC(), WINSIZEX / 2 -50 , WINSIZEY - 120, _time, 0);
	if (_time >= 10) {
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY - 120, (_time - _time % 10) / 10, 0);
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY - 120, _time % 10, 0);
	}
	//���Ű�� ��ư ������ �ش��ϴ� ��Ʈ ���� ���ϴ°� �����ֱ�
	//���Ű�� ���ѽð� �����ֱ�
	if (KEYMANAGER->isToggleKey('A')) {
		
		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), gameStartRc[i]);
		}

		RECT temp;
		for (int i = 0; i < 4; i++) {
			if (IntersectRect(&temp, &gameStartRc[i], &gameStartRc[4])) {
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
				FillRect(getMemDC(), &gameStartRc[i], brush);
				_isCheck[i] = true;
				DeleteObject(brush);
			}
		}

		char str[128];
		sprintf(str, "���ѽð�:%d", _time);
		TextOut(getMemDC(), 0, 200, str, strlen(str));
	}
	char str1[128];
	sprintf(str1, "���콺��ǥ:%d,%d", _ptMouse);
	TextOut(getMemDC(), 0, 200, str1, strlen(str1));

}
