#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//����ź ��ź ǥ���Ƿ�Ʈ
	RECT _guageRc;		//��������
	RECT _upRc;			//����Ʈ
	//�׽�Ʈ��
	RECT _score;		//�׽�Ʈ�� ����ź

	int _scorePos;		//����ó�� �ʱ���ġ��ǥ
	int _bombPos;		//����ź ���� �ʱ�ȭ ��ġ��ǥ


	//========================================================
	// �� ���� �̹��� ����
	//========================================================
	image* _bombarmsImg;
	image* _armsImg;
	image* _guageImg;
	image* _1upImg;

	image* _lifeImg;
	image* _infiniteImg;
	image* _bombImg;
	image* _scoreImg;
	image* _buImg;



public:
	playerDataUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~playerDataUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();


};

