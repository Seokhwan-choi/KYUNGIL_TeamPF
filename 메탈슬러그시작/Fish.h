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
	

public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

