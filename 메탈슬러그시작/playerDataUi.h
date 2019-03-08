#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//수류탄 총탄 표기판렉트
	RECT _guageRc;		//게이지바
	RECT _upRc;			//생명렉트
	//========================================================
	// 씬 관련 이미지 변수
	//========================================================
	image* _bombarmsImg;		//틀
	image* _guageImg;			//게이지바테두리
	image* _1upImg;				//1up

	image* _lifeImg;			//생명숫자
	image* _scoreImg;			//점수숫자
	image* _buImg;				//블렛숫자



public:
	playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot );
	~playerDataUi();
	
	HRESULT Init();
	void Release();
	void Update();
	void Render();


};

