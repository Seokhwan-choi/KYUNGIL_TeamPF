#pragma once
#include "GameObject.h"
class stage1StartUi : public GameObject
{
private:
	//========================================================
	//이미지 렉트 
	//========================================================

	RECT startRc[14];			//위쪽 mission1	
	POINTFLOAT _wh;			    //너비높이
	POINTFLOAT _site[14];		//위치
	POINTFLOAT _y;				//y위치 잡아줄 변수
	//========================================================
	//움직임을 위한 변수
	//========================================================
	float _angle;				//렉트 앵글 값
	float _speed;			   //움직일 렉트 스피드
	int _count;				   //몇 초뒤에 움직이고 갈 것이다
	bool _isMove;			   //서로 흩어져서 갈것이냐?
	//이미지 
	image* _textImg[14];

public:
	stage1StartUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~stage1StartUi();

	POINTFLOAT* getSite() { return _site; }

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

