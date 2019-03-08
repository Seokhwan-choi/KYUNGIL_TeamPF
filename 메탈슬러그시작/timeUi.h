#pragma once
#include "GameObject.h"
class timeUi : public GameObject
{
private:
	//�̹��� ��Ʈ ����
	RECT _timeRc;
	
	//Ÿ�� �̹���
	image* _timeImg;
	
	//���ѽð� ����
	int _time;
	int _count;
	
	//���� ���� ������ �Һ���
	bool _isShow;

public:
	timeUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~timeUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void setIsShow(bool isshow) { _isShow = isshow; }
};

