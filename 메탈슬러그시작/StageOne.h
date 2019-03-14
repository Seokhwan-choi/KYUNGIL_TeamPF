#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:

	class Player* _player;
	class Crab* _crab[11];
	class BubbleCrab* _bubbleCrab[8];
	class FlyBug* _flyBug[6];

	image* _bgImage;			// 배경이미지 
	image* _bgSea;				// 배경 출렁출렁
	image* _bgImage2;			// 배경의 배경
	image* _PixelImage;			// 픽셀 충돌용 이미지
	image* _tongImage;			// 통임 
	image* _wallImage;			// 맵장벽
	
	bool _PixelCheck;			// 픽셀 좀 보쟈

	int _index;					// 배경 출렁출렁 프레임 인덱스
	int _count;					// 배경 출렁출렁 프레임 카운트

	int _index2;				// 맵장벽 프레임 인덱스
	int _count2;				// 맵장벽 프레임 카운트

	int _index3;
	int _count3;

	bool _check;


	bool _crush;				// 박았냐?
	RECT _wallRect;				// 막을꺼임

	int _crabCount;				//작은게 수
	int _bubbleCrabCount;		//거품게 수
	int _flyBugCount;			//잠자리 수

	//RECT _test;					// 


	image* _fade;				// fade in/out
	int _fadecount;				// fade 카운트값
	int _alpha;					// fade 알파값 ( 255 원본 , 0 투명 )
	bool _fadein;				// 시작
	bool _fadeout;				// 끝
	
    //##################################좌표테스트용 랙트
	RECT _testRect;
	




public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void PlayerBulletCollisionEnemy();   //플레이어 총알과 적충돌  
	void PlayerCollisionEnemy();         //몬스터와 플레이어 몸통 충돌햇을시 밀려지게 
	void PlayerBoomCollisionBoom();      //플레이어 수류탄과 몬스터 충돌햇을떄 피깍기 
	void ChangeMap(); 

	StageOne() {}
	~StageOne() {}
};
