#pragma once
#include "SingletonBase.h"
#include "enumClaas.h"

class PlayerData :
	public SingletonBase<PlayerData>
{
private:

	int _life;				//생명
	int _bomb;				//수류탄
	int _arms;				//총알갯수
	int _score;				//점수
	int _saveCaptive;		//구한포로수
	
	WEAPON _weapon;	//무기뭐 들고 있냐?~

public:
	PlayerData();
	~PlayerData();

	HRESULT Init();

	//생명
	void setLife(int life) { _life = life; }
	int getLife() { return _life; }

	//수류탄
	void setBomb(int bomb) { _bomb = bomb; }
	int getBomb() { return _bomb; }

	//총알갯수
	void setArms(int arms) { _arms = arms; }
	int getArms() { return _arms; }

	//점수
	void setScore(int score) { _score = score; }
	int getScore() { return _score; }
	
	//구한포로수
	void setCaptive(int captive) { _saveCaptive = captive; }
	int getCaptive() { return _saveCaptive; }

	//무기종류
	enum WEAPON getWeapon() { return _weapon; }
	void setWeapon(WEAPON weapon) { _weapon = weapon; }

};


