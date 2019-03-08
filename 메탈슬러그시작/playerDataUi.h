#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//����ź ��ź ǥ���Ƿ�Ʈ
	RECT _guageRc;		//��������
	RECT _upRc;			//����Ʈ
	//========================================================
	// �� ���� �̹��� ����
	//========================================================
	image* _bombarmsImg;
	image* _guageImg;
	image* _1upImg;

	image* _lifeImg;
	image* _scoreImg;
	image* _buImg;



public:
	playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot );
	~playerDataUi();
	
	HRESULT Init();
	void Release();
	void Update();
	void Render();


};

