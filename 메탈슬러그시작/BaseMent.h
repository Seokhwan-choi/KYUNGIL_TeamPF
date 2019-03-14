#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:

	class Player* _player;  
	image* _bgImage;			// 배경 이미지
	image* _pixelImage;			// 배경 픽셀 이미지

	class BigCrab* _bigCrab;


	image* _Out;				// 나오는 곳 이미지
	int _count;					// 나오는 곳 이미지 프레임 카운트
	int _index;					// 나오는 곳 이미지 프레임 인덱스

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

