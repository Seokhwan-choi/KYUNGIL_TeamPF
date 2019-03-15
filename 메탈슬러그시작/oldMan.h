#pragma once
#include "GameObject.h"
class OldMan : public GameObject
{
private:
	CAPTIVE _captive;
	CAPTIVESTATE _state;
	RUMISTATE _rumistate;
	RECT _tiedRc;
	RECT _tiedcolRc;
	//프레임 이미지 관련 변수
	int _index;
	int _index1;
	int _count;
	int _count1;
	int _t;
	int _time;		//묶여잇는 포로 풀기위한 시간변수
	//움직이는 범위
	POINTFLOAT _range;
	//포로 관련
	RECT _colRc[3];		//포로 충돌 렉트
	int _coly;			//충돌탐지
	float _speed;		//포로스피드
	float _gravity;		//포로 중력값
	//불 변수
	bool _isRight;		//오른쪽이냐?
	bool _isCrush;		//부딪혓냐?
	bool _isGo;			//왼쪽으로 달려나간다
	bool _isShot;		//쐇냐?
	bool _isSave;		//구했냐?
	RECT _temp;
	bool _touch;       //닿았냐?
	


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void setShot(bool isshot) { _isShot = isshot; }
	bool getShot() { return _isShot; }

	RECT* getRect() { return _colRc; }
	void motion();
	void tied();
	void move();

};

