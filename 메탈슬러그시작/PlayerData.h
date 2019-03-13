#pragma once
#include "SingletonBase.h"
#include "enumClaas.h"

class PlayerData :
	public SingletonBase<PlayerData>
{
private:

	int _life;				//����
	int _bomb;				//����ź
	int _arms;				//�Ѿ˰���
	int _score;				//����
	int _saveCaptive;		//�������μ�
	
	WEAPON _weapon;	//���⹹ ��� �ֳ�?~

public:
	PlayerData();
	~PlayerData();

	HRESULT Init();

	//����
	void setLife(int life) { _life = life; }
	int getLife() { return _life; }

	//����ź
	void setBomb(int bomb) { _bomb = bomb; }
	int getBomb() { return _bomb; }

	//�Ѿ˰���
	void setArms(int arms) { _arms = arms; }
	int getArms() { return _arms; }

	//����
	void setScore(int score) { _score = score; }
	int getScore() { return _score; }
	
	//�������μ�
	void setCaptive(int captive) { _saveCaptive = captive; }
	int getCaptive() { return _saveCaptive; }

	//��������
	enum WEAPON getWeapon() { return _weapon; }
	void setWeapon(WEAPON weapon) { _weapon = weapon; }

};


