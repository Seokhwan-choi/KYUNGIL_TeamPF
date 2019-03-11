#pragma once
#include "GameObject.h"
class GameOverUi : public GameObject
{
private:
	//========================================================
	//이미지 렉트 선언
	//========================================================
	//중앙
	RECT numberRc;				//숫자
	RECT continueRc;			//continue	
	//위
	RECT topnumberRc;			//위쪽숫자
	RECT topcontinueRc;			//위쪽컨디뉴렉트
	//========================================================
	//이미지 변수
	//========================================================
	image* _numberImage;		//숫자 이미지
	image* _continueImage;		//continue 이미지
	image* _gameOverImage;		//게임오버 이미지
	
	//========================================================
	//이미지 변수 int형 선언
	//========================================================
	int _number;
	//========================================================
	//프레임관련 변수
	//========================================================
	int _count;
	int _index;
	//========================================================
	//불변수
	//========================================================
	bool _isShow;	//제한시간 및 목숨이 0 일시 true로 변환 해줌

public:

	GameOverUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~GameOverUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();	
	void gameOver();
	void setIsShow(bool isshow) { _isShow = isshow; }	
};

