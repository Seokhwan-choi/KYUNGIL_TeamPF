#pragma once
#include "GameObject.h"
//���� ó�� �� ���� 
class startUi : public GameObject
{
private:
	//========================================================
	// �� ���� �̹��� ����
	//========================================================
	image* _startBgImage;
	//========================================================
	// ������ ���� ���� ����
	//========================================================
	int _count;
	int _index;

	
public:

	startUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~startUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

