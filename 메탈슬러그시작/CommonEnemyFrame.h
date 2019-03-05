#pragma once

typedef enum class state
{
	IDLE,				//��� ����
	L_IDLE,				//���� ������
	R_IDLE,				//������ ������
	ATTACK,				//���� ����
	L_ATTACK_MOVE,		//������ ���� ���� �̵� ����
	R_ATTACK_MOVE,		//������ ���� ������ �̵� ����
	L_ATTACK,			//���� ���� ����
	R_ATTACK,			//������ ���� ����
	L_ATTACK_FINISH,	//���� ���� �Ϸ�
	R_ATTACK_FINISH,	//������ ���� �Ϸ�
	L_MOVE,				//�������� �̵� ����
	R_MOVE,				//���������� �̵� ����
	DEATH				//���� ����
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
	bool isCrush;		//�÷��̾� �Ѿ˰� �浹����
	bool isKill;		//�÷��̾�� �浹����
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
