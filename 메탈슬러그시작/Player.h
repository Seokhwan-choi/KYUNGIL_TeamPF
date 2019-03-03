#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//�÷��̾� �Ѿ��� ������� 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE , IDLE 
};

enum class PLAYERHEAVYSTATE//�÷��̾� �غ�ӽŰ��ϋ� 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, IDLE
};


class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//�÷��̾� �Ѿ� ���� 
	PLAYERHEAVYSTATE _playerheavystate; //�÷��̾� �غ�ӽŰ��ϋ� 
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






public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

