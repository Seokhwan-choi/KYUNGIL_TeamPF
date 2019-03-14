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
	int _count;
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
	RECT _colR;			//�����ִ� ���� �浹 ��Ʈ
	bool _crush;	  //�浹�޳�


public:
	OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item);
	~OldMan();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void setShot(bool isshot) { _isShot = isshot; }
	bool getShot() { return _isShot; }

	//RECT* getRect() { return _colRc; }
	//void setRect(int index,RECT _RC) { _colRc[index] = _RC; }
	RECT getRect() { return _colR; }
	void SetRect(RECT colr) { _colR = colr; }
	void motion();
	void tied();
	void move();

};

