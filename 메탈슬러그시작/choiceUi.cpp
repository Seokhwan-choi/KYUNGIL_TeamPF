#include "stdafx.h"
#include "choiceUi.h"
//========================================================
//���� 
//========================================================
/*
���ý� �������� ���� ������ �ε���Ʈ�簪�� �ְ� �ö�
*/


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
	//�÷� ��Ʈ �������ֱ�
	colorRc[0] = RectMake(76, 309, 269, 535); //ĳ���� ���� 4�� ��Ʈ ��ġ
	colorRc[1] = RectMake(362, 309, 269, 535);
	colorRc[2] = RectMake(648, 309, 269, 535);
	colorRc[3] = RectMake(935, 309, 269, 535);

	//������ �ö󰡴� �� ������ֱ�
	door[0] = RectMake(76,309,269, 535);
	door[3] = RectMake(362, 309, 269, 535);
	door[2] = RectMake(648, 309, 269, 535);
	door[1] = RectMake(935, 309, 269, 535);

	//����� ������ p1������ ��Ʈ �����ϱ�
	moveRc[0] = RectMake(130, 203, 122, 77);
	moveRc[1] = RectMake(438, 203, 122, 77);
	moveRc[2] = RectMake(726, 203, 122, 77);
	moveRc[3] = RectMake(998, 203, 122, 77);
	//������ ��Ʈ �������ֱ�
	downDoorRc = RectMake(648, -226, 269, 535);
	//========================================================
	// bool �ʱ�ȭ
	//========================================================

	for (int i = 0; i < 4; i++) {
		_isCheck[i] = false;													//ĳ���� �����ֱ����� �Ұ� �ʱ�ȭ
		_goUp[i] = false;														//������ ĳ���� �����ֱ� ���� �� ��Ʈ �ø��� ���� �Ұ�
	}
	_doorUp = false;
	_stop = false;
	//========================================================
	// ������ ��Ʈ �ʱ�ȭ
	//========================================================
	_position = { 219,422 };
	gameStartRc[4] = RectMake(_position.x, _position.y, 30, 30);				//������ ��Ʈ �ʱ�ȭ
	
	//========================================================
	// true ���� �ε��� ���� ���� �ʱ�ȭ
	//========================================================
	_a = 0;																		//Ư�� true�� ���� �ε����� ��� ���� �ʱ�ȭ
	
	//========================================================
	// �ð� ���� ���� �ʱ�ȭ
	//========================================================
	_count = 0;																	
	_time = 30;				//���ѽð� �ʱ�ȭ


	//========================================================
	// �̹��� ���� ���� �ʱ�ȭ
	//========================================================
	_index = 0;
	_background = IMAGEMANAGER->addImage("choiceimage", "UI/character_main.bmp", 1280, 960, true, RGB(255,0,255));
	_timeImage = IMAGEMANAGER->addFrameImage("timenumber", "UI/scoreNumber.bmp", 500, 48, 10, 1, true, RGB(0, 248, 0));
	_doorImage = IMAGEMANAGER->addImage("door", "UI/door.bmp", 271, 535, true, RGB(255, 0, 255));
	
	//ĳ���� ���� ���� �ʾ��� ��  ������ �̹��� ����
	_characterImage[0] = IMAGEMANAGER->addImage("characterblack1", "UI/marco_black.bmp", 271, 535);
	_characterImage[1] = IMAGEMANAGER->addImage("characterblack2", "UI/eri_black.bmp", 271, 535);
	_characterImage[2] = IMAGEMANAGER->addImage("characterblack3", "UI/tarma_black.bmp", 271, 535);
	_characterImage[3] = IMAGEMANAGER->addImage("characterblack4", "UI/pio_black.bmp", 271, 535);

	//��ư���� ĳ���� ����â �̹��� �ٲ�°� ����
	_colorchaImage[0] = IMAGEMANAGER->addImage("charactercolor1", "UI/marco_color.bmp", 271, 535);
	_colorchaImage[1] = IMAGEMANAGER->addImage("charactercolor2", "UI/eri_color.bmp", 271, 535);
	_colorchaImage[2] = IMAGEMANAGER->addImage("charactercolor3", "UI/tarma_color.bmp", 271, 535);
	_colorchaImage[3] = IMAGEMANAGER->addImage("charactercolor4", "UI/pio_color.bmp", 271, 535);

	//���õ� ĳ���� �̹��� �������ֱ� - �׽�Ʈ
	_choicechaImage[0] = IMAGEMANAGER->addImage("characterchoice1", "UI/marco_choice.bmp", 271, 514);
	_choicechaImage[1] = IMAGEMANAGER->addImage("characterchoice2", "UI/eri_choice.bmp", 271, 514);
	_choicechaImage[2] = IMAGEMANAGER->addImage("characterchoice3", "UI/tarma_choice.bmp", 271, 514);
	_choicechaImage[3] = IMAGEMANAGER->addImage("characterchoice4", "UI/pio_choice.bmp", 271, 514);

	//p1����� ������
	_yellow = IMAGEMANAGER->addFrameImage("yellowred", "UI/yellow_p2.bmp", 244, 77, 2,1, true, RGB(255,0,255));
	//ĳ���� ���� �� ���� �������鼭 ĳ���� ������ ������ �̹���
	_downDoorImage = IMAGEMANAGER->addFrameImage("downcharacter", "UI/down_tarma.bmp", 1084, 535, 4, 1, true, RGB(255, 0, 255));
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
	//��ó�� �ö󰡴� DOOR
	if (_doorUp == true) {
		for (int i = 0; i < 4; i++) {
			door[i].bottom -= 6 * i + 14;
			door[i].top -= 6 * i + 14;
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
	//���õ� �̹��� �����ֱ� �������� �����ֱ�
	if (_goUp[_a] == true) {
		_isDown = true;
		downDoorRc.bottom += 15;
		downDoorRc.top += 15;
	}
	//�������鼭 �̹��� ���� ���ֱ�
	if (_isDown == true) {
	
		_downDoorImage->setFrameY(0);
		if (_count % 25 == 0) {
			_index++;
			if (_index > 4) {
				_index = 0;
			}
			_downDoorImage->setFrameX(_index);
		}		
	}
	//���� ���̻� �������� ���ϵ��� �����ֱ�
	if (downDoorRc.bottom >= 839) {
		downDoorRc.bottom = 839;
		downDoorRc.top = 839 - 535;
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
			//SCENEMANAGER->ChangeScene("�ΰ���")
		}
	}

	//����� ������ ��� ��¦��¦�Ÿ����Ѵ�
	_yellow->setFrameY(0);
	if (_count % 20 == 0) {
		_index++;
		if (_index > 1) {
			_index = 0;
		}
		_yellow->setFrameX(_index);
	}

	this->UpdateRectByPivot();	// RECT �׷��ش�.

}

void choiceUi::Render()
{
	RECT temp;
	
	//�� �ö󰡰� ���� ������ ���� ĳ����
	if (_doorUp == true){
		for (int i = 0; i < 4; i++) {
			_characterImage[i]->render(getMemDC(), characterRc[i].left, characterRc[i].top);
		}
	}
	//�Ⱥ��̴� ��Ʈ�� ��� ĳ���Ϳ� �浹 ������ ������ �̹��� �����ϱ�
	for (int i = 0; i < 4; i++) {
		if (IntersectRect(&temp, &characterRc[i], &gameStartRc[4])) {
			_isCheck[i] = true;
			_a = i;
		}
	}
	//�Ⱥ��̴� ��Ʈ�� �浹 ������ �÷��� ĳ���� �����ֱ�
	if (_isCheck[_a] == true) {
		_colorchaImage[_a]->render(getMemDC(), colorRc[_a].left, colorRc[_a].top);
	}
	//���ö󰡵��� �ϴ°�
	for (int i = 0; i < 4; i++)
	{
		_doorImage->render(getMemDC(), door[i].left, door[i].top);
	}
	//����ȭ�� â �����ֱ�
	if (_goUp[_a] == true) {
		_choicechaImage[_a]->render(getMemDC(), colorRc[_a].left, colorRc[_a].top);
	}
	if (_isDown == true) {
		_downDoorImage->frameRender(getMemDC(), downDoorRc.left, downDoorRc.top);
	}


	_background->render(getMemDC(), 0, 0);

	if (_isCheck[_a] == true) {
		_yellow->frameRender(getMemDC(), moveRc[_a].left, moveRc[_a].top);
	}
	//���ѽð� ǥ��
	if (_time < 10) _timeImage->frameRender(getMemDC(), WINSIZEX / 2 -50 , WINSIZEY - 120, _time, 0);
	if (_time >= 10) {
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY - 120, (_time - _time % 10) / 10, 0);
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY - 120, _time % 10, 0);
	}
	//���õ� �̹��� �����ֱ� �������� �����ֱ�
	//if (_goUp[_a] == true) {
	//	if (_count % 200 == 0) {
	//		_isDown = true;
	//	}
	//}
	//���Ű�� ��ư ������ �ش��ϴ� ��Ʈ ���� ���ϴ°� �����ֱ�
	//���Ű�� ���ѽð� �����ֱ�
	if (KEYMANAGER->isToggleKey('A')) {
		
		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), gameStartRc[i]);
		}
		//�Ⱥ��̴� ��Ʈ �����Ͽ��� ��ĥ�ǰԲ� �����ֱ�
		for (int i = 0; i < 4; i++) {
			if (IntersectRect(&temp, &gameStartRc[i], &gameStartRc[4])) {
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
				FillRect(getMemDC(), &gameStartRc[i], brush);
				_isCheck[i] = true;
				DeleteObject(brush);
			}
		}
		Rectangle(getMemDC(), gameStartRc[4]);
		//�÷��̹��� ĳ���� ��Ʈ 
		//for (int i = 0; i < 4; i++) {
		//	Rectangle(getMemDC(), colorRc[i]);
		//}
		
		char str[128];
		sprintf(str, "���ѽð�:%d", _time);
		TextOut(getMemDC(), 0, 200, str, strlen(str));
	}
	//�׽�Ʈ ���ý� �� �������� Ȯ��
	//_choicechaImage[0]->render(getMemDC(), colorRc[0].left, colorRc[0].top);



	char str1[128];
	sprintf(str1, "���콺��ǥ:%d,%d", _ptMouse);
	TextOut(getMemDC(), 0, 200, str1, strlen(str1));
	

}
