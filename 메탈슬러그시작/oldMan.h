#pragma once
#include "GameObject.h"
class OldMan : public GameObject
{
private:
	CAPTIVE _captive;
	CAPTIVESTATE _state;
	
	//프레임 이미지 관련 변수
	int _index;
	int _count;
	int _t;
	//움직이는 범위
	POINTFLOAT _range;
	//포로 관련
	RECT _colRc[3];		//포로 충돌 렉트
	float _speed;		//포로스피드
	float _gravity;		//포로 중력값
	bool _isRight;		//오른쪽이냐?
	bool _isCrush;		//부딪혓냐?
	bool _isGo;			//왼쪽으로 달려나간다


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);
	void motion();
	void tied();
	void move();
};

