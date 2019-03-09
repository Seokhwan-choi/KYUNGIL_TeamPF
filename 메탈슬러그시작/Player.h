#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	RECT gameStartRc[5];	//사각형 5개 선언하기
	POINT _center;			//마지막인덱스의 움직일 렉트 포인트 설정
	bool _isCheck[4];		//goUp 인덱스 접근하기 위한 불값선언
	bool _goUp[4];			//인덱스 하나 접근해서 하나만 렉트 올리려고 선언한 불값선언
	bool _isShow;			//캐릭터 보여줬는가 선언해주는 함수
	int a;					//i를 넣기위해서 선언한 정수 선언
	int _time;
	int _mainSceneTime;		//캐릭터선택 제한 시간
	
	
public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();

	HRESULT Init();
	void Release();
	void Update();
	void Render();	
};

