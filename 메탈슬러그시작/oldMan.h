#pragma once
#include "GameObject.h"
class OldMan : public GameObject
{
private:
	CAPTIVE _captive;
	CAPTIVESTATE _state;
	RUMISTATE _rumistate;
	RECT _tiedRc;
	RECT _tiedcolRc;
	//������ �̹��� ���� ����
	int _index;
	int _index1;
	int _count;
	int _count1;
	int _t;
	int _time;		//�����մ� ���� Ǯ������ �ð�����
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
	bool _isSave;		//���߳�?
	RECT _temp;
	bool _touch;       //��ҳ�?
	


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void setShot(bool isshot) { _isShot = isshot; }
	bool getShot() { return _isShot; }

	RECT* getRect() { return _colRc; }
	void motion();
	void tied();
	void move();

};

