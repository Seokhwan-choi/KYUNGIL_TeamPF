#pragma once
#include "GameObject.h"

class OldMan : public GameObject
{
private:
	// =========================================
	// ############## ���� ���� ##############
	// =========================================
	CAPTIVESTATE _state;	//����ó��
	bool _isRight;			//���� ���� ����
	bool _isCrush;			//�÷��̾�� �浹�߳�?
	float _speed;			//���� ���ǵ�
	POINTFLOAT _move;		//���ΰ� �����̴� ����-��

	float _gravity;			//�׽��߷°��ش�

	// =========================================
	// ############## ���� �̹��� ##############
	// =========================================
	int _count;				
	int _index;

	// =========================================
	// ############## ���� ��Ʈ ##############
	// =========================================
	RECT _colRc[2];			//������ ���� �浹 ��Ʈ


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~OldMan();
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void captive1();
	void captive2();

};

