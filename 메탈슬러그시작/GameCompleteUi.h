#pragma once
#include "GameObject.h"
class GameCompleteUi : public GameObject
{
private:
	//========================================================
	//이미지 렉트 
	//========================================================
	RECT completeRc[17];			//위쪽 mission1	
	POINTFLOAT _wh;			    //너비높이
	POINTFLOAT _site[17];		//위치
	POINTFLOAT _y;				//y위치 잡아줄 변수

	//========================================================
	//움직임을 위한 변수
	//========================================================
	float _angle;				//렉트 앵글 값
	float _speed;			   //움직일 렉트 스피드
	int _count;				   //몇 초뒤에 움직이고 갈 것이다
	bool _isMove;			   //서로 흩어져서 갈것이냐?
	
						
	image* _textImg[17];	   //미션1컴플리트!이미지


public:
	GameCompleteUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~GameCompleteUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

