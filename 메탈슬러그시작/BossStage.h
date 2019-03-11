#pragma once
#include "SceneMaker.h"
class BossStage : public SceneMaker
{

private:
	image* _bgImage;			// 보스 스테이지 배경 이미지
	RECT _ground[11];			// 보스 스테이지 바닥 RECT ( 바닥 RECT 11개 )
	image* _groundImage[11];	// 보스 스테이지 바닥 Image
	bool _check[11];			// 보스 스테이지 바닥 없어졌냐 ?
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BossStage() {}
	~BossStage() {}
};

