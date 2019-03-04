#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//�÷��̾� �⺻�Ѿ��� ������� 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE ,DOWNATTACK, IDLE 
};

enum class PLAYERHEAVYSTATE//�÷��̾� �غ�ӽŰ��ϋ� 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE
};

enum class PLAYERWEAPONSTATE//�÷��̾��� ���� ������մ°�? 
{
	NORMAL,HEAVY 
};  //�⺻�Ѿ˰� ���ӽŰ��� ����ִ� 

class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//�÷��̾� �Ѿ� ���� 
	PLAYERHEAVYSTATE _playerheavystate; //�÷��̾� �غ�ӽŰ��ϋ� 
	PLAYERWEAPONSTATE _playerweaponstate;//�÷��̾� ���� ������ճ� ���°�
   //�÷��̾� �Ѿ� 
	Bullet*_playerbullet;//�÷��̾��� �����Ѿ� 
	Boom* _playerboom; //�÷��̾��� ��ź 

	//�÷��̾� ���� 
	float _jumppower;//�÷��̾� ������
	float _gravity;//�÷��̾� �߷� 
	bool _isJump; //�÷��̾� �������³�? 

	
	//�������̹��� 
	int _frameCount;//�÷��̾� �̹��� �ð����� 
	int _frameIndex; //�÷��̾� �̹��� �δ콺 
	bool _isLeft;//���ʻ��³�?

	int _count;		// ���ӽŰ� 4�߽�� _fire�� false�� �ٲ۴� 0���� �ʱ�ȭ�ϰ� 
	float _angle;	// Ȯ�ο� angle
	bool _fire;		// Ȯ�ο� fire
	int _time;		// Ȯ�ο� time
	float _angle1;//����Ȯ�ο�ޱ� ������ �����϶��� �������� ������ �������Ѵ� 

	int _playerboomMax;//�÷��̾� ��ź �ִ밹�� 
	bool _playerboomFire;//0�����ϰ� �Ǹ� ��ź�� ����Ҽ������� 


public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

