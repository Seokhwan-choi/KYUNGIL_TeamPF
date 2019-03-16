#pragma once
#include "SceneMaker.h"

typedef struct tagBridge
{
	RECT rc;
	image* bridgeImg;
	bool isCrush;
}BRIDGE, *LBRIDGE;


typedef struct PixeltagBridge
{
	RECT rc;
	image* bridgeImg;
	bool isCrush;
	bool isShow;
}PIXEL, *LPIXEL;

class BossStage : public SceneMaker
{
private:
	//class Player*_player; 
	image* _bgImage;			// 보스 스테이지 배경 이미지
	image* _waterground;		// 보스 스테이지 출렁 이미지

	BRIDGE _bridge[22];			// 다리 구조체
	PIXEL _pixelbridge[22];		// 픽셀다리 구조체
	bool _start;				// 보스 등장했냐 ?
	//image* _breakImage;		// 보스 등장하면서 부서질 바닥

	int _loopX;					// 보스 스테이지 배경 루프값
	int _gcount;				// 보스 스테이지 출렁 프레임 카운트
	int _gframe;				// 보스 스테이지 출렁 프레임 인덱스

	bool _reset[2];				//다리 리셋 유무

	class Player* _player;
	class Boss* _boss;
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	PIXEL getPixel(int i) { return _pixelbridge[i]; }
	image* getImage(int i) { return _pixelbridge[i].bridgeImg; }
	BRIDGE getBridge(int i) { return _bridge[i]; }

	void PlayerBulletBoss(); //플레이어 총알과 보스 충돌햇을시 
	


	BossStage() {}
	~BossStage() {}
};
