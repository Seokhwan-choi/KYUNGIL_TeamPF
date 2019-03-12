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
	int _coly;			//�浹Ž��
	float _speed;		//���ν��ǵ�
	float _gravity;		//���� �߷°�
	//�� ����
	bool _isRight;		//�������̳�?
	bool _isCrush;		//�ε�����?
	bool _isGo;			//�������� �޷�������
	bool _isShot;		//�i��?
	RECT _temp;
	bool _touch;       //��ҳ�?
	


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);


	void motion();
	void tied();
	void move();

};

