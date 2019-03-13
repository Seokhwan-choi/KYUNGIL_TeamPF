#pragma once
#include "GameObject.h"
class totalScore :
	public GameObject
{
private:
	RECT _ScoreRc;		//���� ���� ����
	RECT _saveRc;		//���� ���� ��������
	RECT _milRc;		//���� �����Ұ�
	RECT _imgRc;		//�����̹���
	RECT _frameRc;		//������ Ʋ 
	RECT _xRc;			//������Ʈ
	RECT _nameRc;		//�̸��ִ� ��Ʈ
	RECT _totalRc;		//�ջ귺Ʈ
	int _count;
	int _index;
	int _saveNum;		//���� ���� �־��ֱ� ���� ����
	bool _isSave;		//���� ���ڶ� ����?

public:
	totalScore(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~totalScore();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

