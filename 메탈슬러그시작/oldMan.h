#pragma once
#include "GameObject.h"

class OldMan : public GameObject
{
private:
	// =========================================
	// ############## 포로 상태 ##############
	// =========================================
	CAPTIVESTATE _state;	//상태처리
	bool _isRight;			//포로 보는 방향
	bool _isCrush;			//플레이어와 충돌했냐?
	float _speed;			//포로 스피드
	POINTFLOAT _move;		//포로가 움직이는 시작-끝

	float _gravity;			//항시중력값준다

	// =========================================
	// ############## 포로 이미지 ##############
	// =========================================
	int _count;				
	int _index;

	// =========================================
	// ############## 포로 렉트 ##############
	// =========================================
	RECT _colRc[2];			//오른쪽 왼쪽 충돌 렉트


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~OldMan();
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void captive1();
	void captive2();

};

