#pragma once
#include "GameObject.h"
class GameOverUi : public GameObject
{
private:
	//========================================================
	//�̹��� ��Ʈ ����
	//========================================================
	//�߾�
	RECT numberRc;				//����
	RECT continueRc;			//continue	
	//��
	RECT topnumberRc;			//���ʼ���
	RECT topcontinueRc;			//�������𴺷�Ʈ
	//========================================================
	//�̹��� ����
	//========================================================
	image* _numberImage;		//���� �̹���
	image* _continueImage;		//continue �̹���
	image* _gameOverImage;		//���ӿ��� �̹���
	
	//========================================================
	//�̹��� ���� int�� ����
	//========================================================
	int _number;
	//========================================================
	//�����Ӱ��� ����
	//========================================================
	int _count;
	int _index;
	//========================================================
	//�Һ���
	//========================================================
	bool _isShow;	//���ѽð� �� ����� 0 �Ͻ� true�� ��ȯ ����

public:

	GameOverUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~GameOverUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();	
	void gameOver();
	void setIsShow(bool isshow) { _isShow = isshow; }	
};

