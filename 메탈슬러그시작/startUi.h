#pragma once
#include "GameObject.h"
//제일 처음 씬 관련 
class startUi : public GameObject
{
private:
	//========================================================
	// 씬 관련 이미지 변수
	//========================================================
	image* _startBgImage;
	//========================================================
	// 프레임 선택 순서 변수
	//========================================================
	int _count;
	int _index;

	
public:

	startUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~startUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

