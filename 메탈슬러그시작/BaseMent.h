#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:

	class Player* _player;  
	image* _bgImage;					// 배경 이미지
	image* _pixelImage;					// 배경 픽셀 이미지

	class Fish* _fish;					//물고기
	class BubbleCrab* _bubbleCrab[10];	//거품게
	class BigCrab* _bigCrab[3];			//큰게


	image* _Out;						// 나오는 곳 이미지
	int _count;							// 나오는 곳 이미지 프레임 카운트
	int _index;							// 나오는 곳 이미지 프레임 인덱스

	int _bubbleCrabCount;				//거품게 수
	int _bigCrabCount;					//큰게 수
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

