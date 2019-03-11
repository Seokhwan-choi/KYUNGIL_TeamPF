#pragma once

typedef enum class state
{
	IDLE,						//��� ����
	L_IDLE,						//���� ������
	R_IDLE,						//������ ������
	ATTACK,						//���� ��
	BACK_MOVE,					//������ ���� �ڷ� �̵�(����)
	ATTACK_FINISH,				//���� ����
	L_ATTACK_MOVE,				//������ ���� ���� �̵� ����
	R_ATTACK_MOVE,				//������ ���� ������ �̵� ����
	L_ATTACK,					//���� ���� ���� ����
	R_ATTACK,					//������ ���� ���� ����
	L_ATTACK_FINISH,			//���� ���� �Ϸ�
	R_ATTACK_FINISH,			//������ ���� �Ϸ�
	L_BUBBLE_SHOOT_MOVE,		//��ǰ ������ ���� ���� �̵� ����
	R_BUBBLE_SHOOT_MOVE,		//��ǰ ������ ���� ������ �̵� ����
	L_BUBBLE_SHOOT_FINISH,		//���� ��ǰ ���� ����
	R_BUBBLE_SHOOT_FINISH,		//���� ��ǰ ���� ����
	L_MOVE,						//�������� �̵� ����
	R_MOVE,						//���������� �̵� ����
	DEATH,						//���� ����
	L_DEATH,					//���� ���� ����
	R_DEATH						//������ ���� ����
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
	bool isCrush;		//�Ѿ˰� �浹����
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

typedef struct tagShoot
{
	POINTFLOAT pt;
	RECT rc;
}
SHOOT, *LSHHOT;
