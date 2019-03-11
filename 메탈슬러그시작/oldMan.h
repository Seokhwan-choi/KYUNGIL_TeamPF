#pragma once
#include "GameObject.h"
class OldMan : public GameObject
{
private:
	CAPTIVE _captive;
	CAPTIVESTATE _state;
	
	//������ �̹��� ���� ����
	int _index;
	int _count;
	int _t;
	//�����̴� ����
	POINTFLOAT _range;
	//���� ����
	RECT _colRc[3];		//���� �浹 ��Ʈ
	float _speed;		//���ν��ǵ�
	float _gravity;		//���� �߷°�
	bool _isRight;		//�������̳�?
	bool _isCrush;		//�ε�����?
	bool _isGo;			//�������� �޷�������


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);
	void motion();
	void tied();
	void move();
};

