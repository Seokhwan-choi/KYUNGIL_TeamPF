#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:
	class Player* _player;
	class BubbleCrab* _boss;
	class Crab* _crab;

	image* _bgImage;			// 배경이미지 
	image* _bgSea;				// 배경 출렁출렁
	image* _bgImage2;			// 배경의 배경
	image* _PixelImage;			// 픽셀 충돌용 이미지

	image* _wallImage;			// 맵장벽

	bool _PixelCheck;			// 픽셀 좀 보쟈

	int _index;					// 배경 출렁출렁 프레임 인덱스
	int _count;					// 배경 출렁출렁 프레임 카운트

	int _index2;				// 맵장벽 프레임 인덱스
	int _count2;				// 맵장벽 프레임 카운트


	bool _crush;				// 박았냐?
	RECT _wallRect;				// 막을꺼임

	RECT _test;					// 
public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void PlayerBulletCollisionEnemy();   //플레이어 총알과 적충돌  
	void PlayerCollisionEnemy();         //몬스터와 플레이어 몸통 충돌햇을시 밀려지게 
	StageOne() {}
	~StageOne() {}
};

