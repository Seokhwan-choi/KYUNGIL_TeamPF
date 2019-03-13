#pragma once
#include "GameObject.h"
class totalScore :
	public GameObject
{
private:
	RECT _ScoreRc;		//구한 포로 점수
	RECT _saveRc;		//구한 포로 갯수선언
	RECT _milRc;		//만점 선언할것
	RECT _imgRc;		//포로이미지
	RECT _frameRc;		//프레임 틀 
	RECT _xRc;			//엑스렉트
	RECT _nameRc;		//이름넣는 렉트
	RECT _totalRc;		//합산렉트
	int _count;
	int _index;
	int _saveNum;		//구한 숫자 넣어주기 위한 숫자
	bool _isSave;		//구한 숫자랑 같냐?

public:
	totalScore(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~totalScore();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

