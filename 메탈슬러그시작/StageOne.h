#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:
	class Player* _player;

	image* _bgImage;			// 배경이미지 
	image* _bgSea;				// 배경 출렁출렁

	image* _bgImage2;			// 배경의 배경
	image* _PixelImage;			// 픽셀 충돌용 이미지

	image* _wallImage;			// 맵_장벽

	bool _PixelCheck;			// 픽셀 좀 보쟈

	int _index;					// 프레임 인덱스
	int _count;					// 프레임 카운트

public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	StageOne() {}
	~StageOne() {}
};

