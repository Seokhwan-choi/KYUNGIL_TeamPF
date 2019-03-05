#pragma once
#include "GameObject.h"
//���� ó�� �� ���� 
class startUi : public GameObject
{
private:
	//========================================================
	// �� ���� ����( size : 1280x960 )
	//========================================================
	image* _startBgImage;
	//========================================================
	// ������ ���� ���� ����( size : 1280x960 )
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

