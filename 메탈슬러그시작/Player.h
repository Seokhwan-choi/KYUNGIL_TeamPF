#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//�÷��̾� �⺻�Ѿ��� ������� 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE ,DOWNATTACK, IDLE 
};//downattack�� �ޱ׷����� 

enum class PLAYERHEAVYSTATE//�÷��̾� �غ�ӽŰ��ϋ� 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE
};//downattack�� �ޱ׷����� 
enum class PLAYERSWORD
{
	LEFTATTACK,RIGHTATTACK,IDLE //�⺻Į������ ���ʰ� �����ʸ��ִ� 
};

enum class PLAYERWEAPONSTATE//�÷��̾��� ���� ������մ°�? 
{
	NORMAL,HEAVY,SWORD   
};  //�⺻�Ѿ˰� ���ӽŰ� �پ��������� Į�� ����ִ� 

class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//�÷��̾� �Ѿ� ���� 
	PLAYERHEAVYSTATE _playerheavystate; //�÷��̾� �غ�ӽŰ��ϋ� 
	PLAYERSWORD _playersword;//�÷��̾� Į���� ���ʰ� �������ϋ� enum�� 
	PLAYERWEAPONSTATE _playerweaponstate;//�÷��̾� ���� ������ճ� ���°�
   //�÷��̾� �Ѿ� 
	Bullet*_playerbullet;//�÷��̾��� �����Ѿ� 
	Boom* _playerboom; //�÷��̾��� ��ź 

	RECT PlayerLeftSword;//���ʸ���ϋ� Į��Ʈ 
	RECT PlayerRightSword;//�����ʸ���ϋ� Į��Ʈ 

	//=================================
	RECT PlayerRealLeftSword; //��¥ �浹�� ���� Į
	RECT PlayerRealRightSword; //��¥ �浹�� ������ Į

	bool PlayerRealSwordState; //��¥ �浹�� Į�� bool �� 
	int SwordCount; //Į �p�ʵڿ� ���ְ��ҷ��� 


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


	bool _playerboomFire;//0�����ϰ� �Ǹ� ��ź�� ����Ҽ������� 
	//������ó���� bulletŬ���� boom fire�Լ����� ó���Ѵ� 

	

public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

