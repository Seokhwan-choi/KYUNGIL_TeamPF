#include "stdafx.h"
#include "choiceUi.h"
//========================================================
//버그 
//========================================================
/*
선택시 움직였던 제일 마지막 인덱스트루값을 주고 올라감
*/


choiceUi::choiceUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_size = size;
	_pivot = Pivot::LeftTop;
	
	//========================================================
	//렉트 초기화 
	//========================================================
	for (int i = 0; i < 4; i++) {
		gameStartRc[i] = RectMake(76 +286 * i, 309, 286, 535);	//4개 렉트 위치(앞쪽 렉트)
	}
	//흑백 렉트 선언해주기
	characterRc[0] = RectMake(76, 309, 269, 535); //캐릭터 나올 4개 렉트 위치
	characterRc[1] = RectMake(362, 309, 269, 535);
	characterRc[2] = RectMake(648, 309, 269, 535);
	characterRc[3] = RectMake(935, 309, 269, 535);
	//컬러 렉트 선언해주기
	colorRc[0] = RectMake(76, 309, 269, 535); //캐릭터 나올 4개 렉트 위치
	colorRc[1] = RectMake(362, 309, 269, 535);
	colorRc[2] = RectMake(648, 309, 269, 535);
	colorRc[3] = RectMake(935, 309, 269, 535);

	//앞으로 올라가는 문 만들어주기
	door[0] = RectMake(76,309,269, 535);
	door[3] = RectMake(362, 309, 269, 535);
	door[2] = RectMake(648, 309, 269, 535);
	door[1] = RectMake(935, 309, 269, 535);

	//노란색 빨간색 p1움직일 렉트 선언하기
	moveRc[0] = RectMake(130, 203, 122, 77);
	moveRc[1] = RectMake(438, 203, 122, 77);
	moveRc[2] = RectMake(726, 203, 122, 77);
	moveRc[3] = RectMake(998, 203, 122, 77);
	//내려올 렉트 선언해주기
	downDoorRc = RectMake(648, -226, 269, 535);
	//========================================================
	// bool 초기화
	//========================================================

	for (int i = 0; i < 4; i++) {
		_isCheck[i] = false;													//캐릭터 보여주기위한 불값 초기화
		_goUp[i] = false;														//숨겨진 캐릭터 보여주기 위한 앞 렉트 올리기 위한 불값
	}
	_doorUp = false;
	_isDown = false;
	//========================================================
	// 움직일 렉트 초기화
	//========================================================
	_position = { 219,422 };
	gameStartRc[4] = RectMake(_position.x, _position.y, 30, 30);				//움직일 렉트 초기화
	
	//========================================================
	// true 값된 인덱스 담을 변수 초기화
	//========================================================
	_a = 0;																		//특정 true에 대한 인덱스를 담기 위해 초기화	
	//========================================================
	// 시간 관련 변수 초기화
	//========================================================
	_count = 0;																	
	_time = 30;				//제한시간 초기화
	_t = 0;					//게임화면 변환하기 위한 변수
	//========================================================
	// 이미지 관련 변수 초기화
	//========================================================
	_index = 0;
	_background = IMAGEMANAGER->addImage("choiceimage", "UI/choiceScene/character_main.bmp", 1280, 960, true, RGB(255,0,255));
	_timeImage = IMAGEMANAGER->addFrameImage("timenumber", "UI/choiceScene/scoreNumber.bmp", 500, 48, 10, 1, true, RGB(0, 248, 0));
	_doorImage = IMAGEMANAGER->addImage("door", "UI/choiceScene/door.bmp", 271, 535, true, RGB(255, 0, 255));
	
	//캐릭터 선택 되지 않았을 시  나오는 이미지 선언
	_characterImage[0] = IMAGEMANAGER->addImage("characterblack1", "UI/choiceScene/marco_black.bmp", 271, 535);
	_characterImage[1] = IMAGEMANAGER->addImage("characterblack2", "UI/choiceScene/eri_black.bmp", 271, 535);
	_characterImage[2] = IMAGEMANAGER->addImage("characterblack3", "UI/choiceScene/tarma_black.bmp", 271, 535);
	_characterImage[3] = IMAGEMANAGER->addImage("characterblack4", "UI/choiceScene/pio_black.bmp", 271, 535);

	//버튼으로 캐릭터 선택창 이미지 바뀌는것 선언
	_colorchaImage[0] = IMAGEMANAGER->addImage("charactercolor1", "UI/choiceScene/marco_color.bmp", 271, 535);
	_colorchaImage[1] = IMAGEMANAGER->addImage("charactercolor2", "UI/choiceScene/eri_color.bmp", 271, 535);
	_colorchaImage[2] = IMAGEMANAGER->addImage("charactercolor3", "UI/choiceScene/tarma_color.bmp", 271, 535);
	_colorchaImage[3] = IMAGEMANAGER->addImage("charactercolor4", "UI/choiceScene/pio_color.bmp", 271, 535);

	//선택된 캐릭터 이미지 선언해주기 - 테스트
	_choicechaImage[0] = IMAGEMANAGER->addImage("characterchoice1", "UI/choiceScene/marco_choice.bmp", 271, 514);
	_choicechaImage[1] = IMAGEMANAGER->addImage("characterchoice2", "UI/choiceScene/eri_choice.bmp", 271, 514);
	_choicechaImage[2] = IMAGEMANAGER->addImage("characterchoice3", "UI/choiceScene/tarma_choice.bmp", 271, 514);
	_choicechaImage[3] = IMAGEMANAGER->addImage("characterchoice4", "UI/choiceScene/pio_choice.bmp", 271, 514);

	//p1노란색 빨간색
	_yellow = IMAGEMANAGER->addFrameImage("yellowred", "UI/choiceScene/yellow_p2.bmp", 244, 77, 2,1, true, RGB(255,0,255));
	//캐릭터 선택 후 문이 내려오면서 캐릭터 움직임 보여줄 이미지
	_downDoorImage = IMAGEMANAGER->addFrameImage("downcharacter", "UI/choiceScene/down_tarma.bmp", 1084, 535, 4, 1, true, RGB(255, 0, 255));
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
	RECT temp;
	_count++;
	
	//1초에 1씩 감소하도록 만들어 준다 
	if (_count % 100 == 0) {
		_time--;
	}
	//0.5
	if (_count == 20) {
		_doorUp = true;
	}
	//맨처음 올라가는 DOOR
	//불규칙적으로 올라가게끔 처리함
	if (_doorUp == true) {
		for (int i = 0; i < 4; i++) {
			door[i].bottom -= 7 * i + 10;
			door[i].top -= 7 * i + 10;
		}
	}
	if (_count > 100) {
		//오른쪽 눌렀냐 선택 렉트 밖으로 벗어나지 않게끔 제한 설정해줌
		if (_isDown == false) {
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) &&
				(gameStartRc[4].right < 1019)) {
				gameStartRc[4].left += 268;
				gameStartRc[4].right += 268;
			}
			//왼쪽 눌렀냐 선택 렉트  밖으로 벗어나지 않게끔 제한 설정해줌
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT) &&
				(gameStartRc[4].left > 268)) {
				gameStartRc[4].left -= 268;
				gameStartRc[4].right -= 268;
			}
			//엔터 누를시 올라갈 렉트 선정해주기
			//선정된 렉트 i를 _a에 넣어준다
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
				for (int i = 0; i < 4; i++) {
					if (_isCheck[i] == true) {
						_a = i;
						_goUp[_a] = true;
					}
				}
			}
		}
	}
	//선택된 이미지 보여주기 문내리며 보여주기
	if (KEYMANAGER->isStayKeyDown(VK_RETURN) && (IntersectRect(&temp, &colorRc[2], &gameStartRc[4]))) {
		_isDown = true;
	}
	if(_isDown == true){
		downDoorRc.bottom += 25;
		downDoorRc.top += 25;
	}	
	//숨겨진 렉트와 충돌하지 않았을 시 한 번에 선택된 캐릭터창 보여주지 않게끔 예외처리
	for (int i = 0; i < 4; i++) {
		if (!IntersectRect(&temp, &colorRc[i], &gameStartRc[4])) {
			_isCheck[i] = false;
		}
	}
	//시간이 0으로 되면 자동으로 캐릭터 선택 되도록 만들었다
	if (_time == 0) {
		//자동으로 반짝거리게 만들어줌
		gameStartRc[4] = RectMake(gameStartRc[2].left+40, gameStartRc[2].top + 50, 40,40);
		_isDown = true;
	}
	//선정된 렉트를 올려줘 안에 있는 캐릭터를 보여준다
	//노란색 빨간색 계속 반짝반짝거리게한다
	_yellow->setFrameY(0);
	if (_count % 20 == 0) {
		_index++;
		if (_index > 1) {
			_index = 0;
		}
		_yellow->setFrameX(_index);
	}	
	//내려오면서 이미지 랜더 해주기
	if (_isDown == true) {
		_downDoorImage->setFrameY(0);
		if (_count % 12== 0) {
			_index++;
			if (_index > 4) {
				_index = 0;
			}
			_downDoorImage->setFrameX(_index);
		}		
	}
	//문이 더이상 내려가지 못하도록 막아주기
	if (downDoorRc.bottom >= 839) {
		downDoorRc.bottom = 839;
		downDoorRc.top = 839 - 535;
	}
	//2초 뒤에 스테이지 1으로 가게 한다.
	if (_isDown == true ) {
		_t++;
		if(_t == 250) {
			SCENEMANAGER->ChangeScene("스테이지원");
		}		
	}
	this->UpdateRectByPivot();	// RECT 그려준다.
}

void choiceUi::Render()
{
	RECT temp;
	
	//문 올라가고 나서 보여줄 흑백색 캐릭터
	if (_doorUp == true){
		for (int i = 0; i < 4; i++) {
			_characterImage[i]->render(getMemDC(), characterRc[i].left, characterRc[i].top);
		}
	}
	//안보이는 렉트와 흑백 캐릭터와 충돌 됐을시 보여줄 이미지 랜더하기
	for (int i = 0; i < 4; i++) {
		if (IntersectRect(&temp, &characterRc[i], &gameStartRc[4])) {
			_isCheck[i] = true;
			_a = i;
		}
	}
	//안보이는 렉트와 충돌 됐을시 컬러색 캐릭터 보여주기
	if (_isCheck[_a] == true) {
		_colorchaImage[_a]->render(getMemDC(), colorRc[_a].left, colorRc[_a].top);
	}
	//문올라가도록 하는것
	for (int i = 0; i < 4; i++)
	{
		_doorImage->render(getMemDC(), door[i].left, door[i].top);
	}
	//선택화면 창 보여주기
	if (_goUp[_a] == true) {
		_choicechaImage[_a]->render(getMemDC(), colorRc[_a].left, colorRc[_a].top);
	}
	if (_isDown == true) {
		_downDoorImage->frameRender(getMemDC(), downDoorRc.left, downDoorRc.top);
	}
	//배경
	_background->render(getMemDC(), 0, 0);

	if (_isCheck[_a] == true) {
		_yellow->frameRender(getMemDC(), moveRc[_a].left, moveRc[_a].top);
	}
	//제한시간 표기
	if (_time < 10) _timeImage->frameRender(getMemDC(), WINSIZEX / 2 -50 , WINSIZEY - 120, _time, 0);
	if (_time >= 10) {
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY - 120, (_time - _time % 10) / 10, 0);
		_timeImage->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY - 120, _time % 10, 0);
	}
	
	//토글키로 버튼 누를때 해당하는 렉트 색깔 변하는거 보여주기
	//토글키로 제한시간 보여주기
	if (KEYMANAGER->isToggleKey('A')) {
		
		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), gameStartRc[i]);
		}
		//안보이는 렉트 선언하여서 색칠되게끔 보여주기
		for (int i = 0; i < 4; i++) {
			if (IntersectRect(&temp, &gameStartRc[i], &gameStartRc[4])) {
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
				FillRect(getMemDC(), &gameStartRc[i], brush);
				_isCheck[i] = true;
				DeleteObject(brush);
			}
		}
		Rectangle(getMemDC(), gameStartRc[4]);
	
		char str[128];
		sprintf(str, "제한시간:%d", _time);
		TextOut(getMemDC(), 0, 200, str, strlen(str));
	}

	char str1[128];
	sprintf(str1, "마우스좌표:%d,%d", _ptMouse);
	TextOut(getMemDC(), 0, 200, str1, strlen(str1));
	

}
