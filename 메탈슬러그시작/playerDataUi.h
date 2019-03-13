#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//수류탄 총탄 표기판렉트
	RECT _guageRc;		//게이지바
	RECT _upRc;			//생명렉트
	//테스트용
	RECT _score;		//테스트용 수류탄

	int _scorePos;		//점수처리 초기위치좌표
	int _bombPos;		//수류탄 갯수 초기화 위치좌표


	//========================================================
	// 씬 관련 이미지 변수
	//========================================================
	image* _bombarmsImg;
	image* _armsImg;
	image* _guageImg;
	image* _1upImg;

	image* _lifeImg;
	image* _infiniteImg;
	image* _bombImg;
	image* _scoreImg;
	image* _buImg;



public:
	playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~playerDataUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();


};

