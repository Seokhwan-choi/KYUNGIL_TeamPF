#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//수류탄 총탄 표기판렉트
	RECT _guageRc;		//게이지바
	RECT _upRc;			//생명렉트
	RECT _saveRc[10];		//구한생명수 렉트
	POINTFLOAT _center;	//구한생명수 렉트 left top
	RECT _hpRc;			//보스  생명 체력 나타나기위한렉트
	//테스트용
	RECT _score;		//테스트용 수류탄

	int _scorePos;		//점수처리 초기위치좌표
	int _bombPos;		//수류탄 갯수 초기화 위치좌표
	
	//=======================================================
	// 보스만나고 체력 바 체워주기 위한 불변수
	//========================================================
	bool _isMeet;		//보스랑 만났냐?
	bool _isShow[10];		//만세 보여주세요
	int _count;
	
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
	//렉트
	RECT* getRect() { return _saveRc; }
	
	void setRect(POINTFLOAT center);

	//보스랑 만났냐?
	void setMeet(bool meet) { _isMeet = meet; }
};

