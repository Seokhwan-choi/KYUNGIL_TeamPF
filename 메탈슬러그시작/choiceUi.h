#pragma once
#include "GameObject.h"
//캐릭터 선택창 관련
class choiceUi :
	public GameObject
{
private:
	//========================================================
	// 캐릭터 선택 창 뒷 배경관련 변수 
	//========================================================
	
	//========================================================
	// 캐릭터 선택 창 관련 변수 
	//========================================================
	RECT gameStartRc[5];	//사각형 5개 (4개 : 보이는 렉트 1개 : 안보이는 렉트)
	RECT characterRc[4];	//캐릭터 4개 선언
	RECT door[4];			//올라가는 문 만들어주기
	RECT colorRc[4];		//컬러색 이미지 렉트
	RECT moveRc[5];			//노란색빨간색p1 움직일 렉트 선언
	POINT _center;			//마지막인덱스의  움직일 렉트
	RECT downDoorRc;		//내려오는 문 선언해주기
	
	bool _doorUp;			//처음 올릴 문 불값주기
	bool _isCheck[4];		//캐릭터를 보여주기 위한 불값
	bool _goUp[4];			//숨겨진 캐릭터를 보여주기 위해 선택창올리기  위한 불값
	bool _isShow;			//보여줬는가?
	bool _isDown;			//캐릭터 보여줄 것인가?
	bool _stop;				//멈추기 위한 변수

	int _a;					//특정 true값을 담기 위한 변수
	int _count;				//카운터 ++
	int _time;				//제한시간
	int _index;				//프레임이미지 인덱스
	//========================================================
	// 캐릭터 선택 창 이미지 변수
	//========================================================
	image* _timeImage;				//제한시간 이미지 선언하기
	image* _background;				//백그라운드 이미지 선언하기
	image* _doorImage;				//문 이미지
	image* _characterImage[4];		//캐릭터 흑백 이미지
	image* _colorchaImage[4];		//캐릭터 컬러 이미지
	image* _choicechaImage[4];		//캐릭터 선택시 나오는 이미지 선언
	image* _yellow;					//옐로 -> 레드
	image* _downDoorImage;			//캐릭터 선택 후 내려오는 문 이미지
public:
	choiceUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~choiceUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

