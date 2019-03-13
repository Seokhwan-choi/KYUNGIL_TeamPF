#pragma once
#include "GameObject.h"
class Fish : public GameObject
{
private:
	//����
	STATE _state;
	//�÷��̾�
	class Player* player;
	//����� ��Ʈ
	RECT Fish_Rc;
	//ī�޶� ����ü
	CAM _cam;
	//����� ������ ���� ī��Ʈ
	int count;

public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

