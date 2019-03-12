#pragma once
#include "SceneMaker.h"
class BossStage : public SceneMaker
{

private:
	image* _bgImage;			// 보스 스테이지 배경 이미지
	RECT _ground[11];			// 보스 스테이지 바닥 RECT ( 바닥 RECT 11개 )
	image* _groundImage[11];	// 보스 스테이지 바닥 이미지
	image* _waterground;		// 보스 스테이지 출렁 이미지
	image* _breakImage;			// 보스 등장하면서 부서질 바닥
	bool _check[11];			// 보스 스테이지 바닥 없어졌냐 ?
	bool _start;				// 보스 등장했냐 ?

	int _loopX;					// 보스 스테이지 배경 루프값
	int _gcount;				// 보스 스테이지 출렁 프레임 카운트
	int _gframe;				// 보스 스테이지 출렁 프레임 인덱스
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BossStage() {}
	~BossStage() {}
};

