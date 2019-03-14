#pragma once
#include "GameObject.h"

typedef struct fish
{
	//����� ��Ʈ
	RECT Fish_Rc;
	//�Һ���
	bool isFish;
	//ī��Ʈ ����
	int count;
	//�̹��� ������ ����
	int Imgcount[3];
	int Imgindex[3];
	//�̹����� �Һ���
	bool Imgchange;
	//����� ����ī��Ʈ
	int fish_death;
	//����� ü��
	int hp;
	//����� ���� ����
	bool isDeath;
	state _fish_state;
}Fish_t;

class Fish : public GameObject
{
private:
	//����
	STATE _state;
	//�÷��̾�
	class Player* player;
	//ī�޶� ����ü
	CAM _cam;
	//����� ������ ���� ī��Ʈ
	int count;
	//����� ����ü
	Fish_t fish_rc[8];
	//����� �̹���
	image* fishImg[3];
	//ī����
	int count_death;

	int boxhp;

	bool _rc_on;
	bool is;
public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();

	//ü�� get
	int getHp(int i) { return fish_rc[i].hp; }
	//ü�� set
	void setHp(int i, int hp) { fish_rc[i].hp = hp; }
	//����� ��Ʈ get
	RECT getCol(int i) { return fish_rc[i].Fish_Rc; }
	//����� ���� ��Ʈ
	RECT getboxCol() { return _rc; }
	//����� ���� ü�� get
	int getboxHp() { return boxhp; }
	//����� ���� ü�� set
	void setboxHp(int HP) { boxhp = HP; }
	//����� ������
	void fish_damage(int i ,int damage) { fish_rc[i].hp -= damage; }
	//���� ������
	void box_damage(int damage) { boxhp -= damage; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

