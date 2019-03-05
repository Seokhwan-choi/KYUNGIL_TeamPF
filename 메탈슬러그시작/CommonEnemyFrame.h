#pragma once

typedef enum class state
{
	IDLE,				//대기 상태
	L_IDLE,				//왼쪽 대기상태
	R_IDLE,				//오른쪽 대기상태
	ATTACK,				//공격 상태
	L_ATTACK_MOVE,		//공격을 위해 왼쪽 이동 상태
	R_ATTACK_MOVE,		//공격을 위해 오른쪽 이동 상태
	L_ATTACK,			//왼쪽 공격 상태
	R_ATTACK,			//오른쪽 공격 상태
	L_ATTACK_FINISH,	//왼쪽 공격 완료
	R_ATTACK_FINISH,	//오른쪽 공격 완료
	L_MOVE,				//왼쪽으로 이동 상태
	R_MOVE,				//오른쪽으로 이동 상태
	DEATH				//죽음 상태
}
STATE, *LSTATE;

typedef struct tagCamera
{
	POINTFLOAT pt;
	RECT rc;
	bool isCrush;
}
CAM, *LCAM;

typedef struct tagCollision
{
	POINTFLOAT pt;
	RECT rc;
	bool isCrush;		//플레이어 총알과 충돌여부
	bool isKill;		//플레이어와 충돌여부
}
COL, *LCOL;

typedef struct tagPart
{
	POINTFLOAT pt;
	RECT rc;
}
PART, *LPART;

typedef struct tagAttack
{
	POINTFLOAT pt;
	RECT rc;
}
ATTACK, *LATTACK;

typedef struct tagBubble
{
	image* bubbleImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool isFire;
	int count;
}
BUBBLE, *LBUBBLE;
