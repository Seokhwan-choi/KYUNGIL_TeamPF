#pragma once
#include "GameObject.h"
class timeUi : public GameObject
{
private:
	//이미지 렉트 선언
	RECT _timeRc;
	
	//타임 이미지
	image* _timeImg;
	
	//제한시간 변수
	int _time;
	int _count;
	
	//숫자 랜더 없애줄 불변수
	bool _isShow;

public:
	timeUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~timeUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void setIsShow(bool isshow) { _isShow = isshow; }
};

