#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class BubbleCrab : public GameObject
{
private:
	//상태
	STATE _state;
	//상하 움직임 처리를 위한 변수
	bool _isUp;
	//공격 처리를 위한 변수
	int _isStop;					//카메라 센서 정지유무
	int _gauge;						//근접공격 딜레이 처리
	int _bubbleGauge;				//거품공격 딜레이 처리
	float _attackAngle;
	bool _isBubbleShoot;
	bool _isBubbleShootFinish;
	int _moveTimer;
	bool _isAttack;
	bool _isAttackFinish;
	int _hp;

	//죽음 처리를 위한 변수
	int _deathTimer;
	//카메라 구조체
	CAM _cam;	//플레이어를 감지하는 범위 중심점으로 부터 900
					//왔다갔다 공격하는 범위 중심점으로 부터 300
	//충돌 구조체
	COL _col[4];	//0 : top, 1: bottom, 2 : left, 3: right
	//시체처리 구조체
	PART _part[3];	//0 : left, 1 : center, 2 : right 
	//공격처리 구조체
	ATTACK _att[2];	//0 : left, 1 : right
	//플레이어와의 각도
	float _angle;
	//거품발사시 플레이어와의 각도
	float _bubbleAngle;
	//플레이어와의 거리
	float _dist;
	//텍스트
	char msg1[128];
	POINT _pt;
	//플레이어 클래스
	class Player* _player;
	//거품 클래스
	class Bubble* _bubble;
	//이미지
	image* BubblecrabImg[8];
	//이미지 랜더용 변수
	int indexImg[6], countImg[6];

	//픽셀 충돌
	int _probeY;
	image* _pixelImage[2];
	int _pixelGravity;
	RECT _pixelrc;

	bool _bubbleShootSound;	//거품사운드반복재생방지
	bool _deathSound;	//사운드반복재생방지
public:
	BubbleCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BubbleCrab();

	//충돌렉트 get
	RECT getCol(int i) { return _col[i].rc; }
	//공격렉트 get
	RECT getAtt(int i) { return _att[i].rc; }
	//거품렉트 get
	//RECT getbubble(int i) { return _bubble->getVBubble()[i].rc; }
	//체력 get
	int getHp() { return _hp; }
	//체력 set
	void setHp(int hp) { _hp = hp; }

	//데미지
	void bubbleCrab_damage(int damage) { _hp -= damage; }



	//충돌여부 get
	bool getIsCrush(int i) { return _col[i].isCrush; }
	//충돌여부 set
	void setIsCrush(int i, bool crush) { _col[i].isCrush = crush; }
	//플레이어 죽임여부 get
	bool getIsKill(int i) { return _col[i].isKill; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void bubblecrabImage();
	void bubblecrabImageRender();
};


