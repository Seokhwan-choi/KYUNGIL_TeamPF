#pragma once
#include "GameObject.h"
class GameOverUi_2 :
	public GameObject
{
private:
	image* _gameOverImage;		//���ӿ��� �̹���
	//========================================================
	//�����Ӱ��� ����
	//========================================================
	int _count;
	int _index;
	RECT backgroundRc;			//����

	bool _isShow;

public:
	GameOverUi_2(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~GameOverUi_2();
	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void gameOver();
	void setIsShow(bool isshow) { _isShow = isshow; }
};

