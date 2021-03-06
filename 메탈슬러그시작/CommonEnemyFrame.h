#pragma once

typedef enum class state
{
	IDLE,						//대기 상태
	L_IDLE,						//왼쪽 대기상태
	R_IDLE,						//오른쪽 대기상태
	ATTACK,						//공격 중
	BACK_MOVE,					//공격을 위해 뒤로 이동(보스)
	ATTACK_FINISH,				//공격 종료
	L_ATTACK_MOVE,				//공격을 위해 왼쪽 이동 상태
	R_ATTACK_MOVE,				//공격을 위해 오른쪽 이동 상태
	L_ATTACK,					//왼쪽 근접 공격 상태
	R_ATTACK,					//오른쪽 근접 공격 상태
	L_ATTACK_FINISH,			//왼쪽 공격 완료
	R_ATTACK_FINISH,			//오른쪽 공격 완료
	L_BUBBLE_SHOOT_MOVE,		//거품 공격을 위해 왼쪽 이동 상태
	R_BUBBLE_SHOOT_MOVE,		//거품 공격을 위한 오른쪽 이동 상태
	L_BUBBLE_SHOOT_FINISH,		//왼쪽 거품 공격 상태
	R_BUBBLE_SHOOT_FINISH,		//왼쪽 거품 공격 상태
	L_MOVE,						//왼쪽으로 이동 상태
	R_MOVE,						//오른쪽으로 이동 상태
	DEATH,						//죽음 상태
	L_DEATH,					//왼쪽 죽음 상태
	R_DEATH,					//오른쪽 죽음 상태
	FIRECANNON_SHOOT,			//화염포 발사 상태
	BOMB_SHOOT					//폭탄 발사 상태
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

typedef struct tagShoot
{
	POINTFLOAT pt;
	RECT rc;
}
SHOOT, *LSHHOT;
