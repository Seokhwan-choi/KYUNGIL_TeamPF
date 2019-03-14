#pragma once
#include "GameObject.h"
class playerDataUi : public GameObject
{
private:

	RECT _bombArmsRc;	//����ź ��ź ǥ���Ƿ�Ʈ
	RECT _guageRc;		//��������
	RECT _upRc;			//����Ʈ
	RECT _saveRc[10];		//���ѻ���� ��Ʈ
	POINTFLOAT _center;	//���ѻ���� ��Ʈ left top
	RECT _hpRc;			//����  ���� ü�� ��Ÿ�������ѷ�Ʈ
	//�׽�Ʈ��
	RECT _score;		//�׽�Ʈ�� ����ź

	int _scorePos;		//����ó�� �ʱ���ġ��ǥ
	int _bombPos;		//����ź ���� �ʱ�ȭ ��ġ��ǥ
	
	//=======================================================
	// ���������� ü�� �� ü���ֱ� ���� �Һ���
	//========================================================
	bool _isMeet;		//������ ������?
	bool _isShow[10];		//���� �����ּ���
	int _count;
	
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
	//��Ʈ
	RECT* getRect() { return _saveRc; }
	
	void setRect(POINTFLOAT center);

	//������ ������?
	void setMeet(bool meet) { _isMeet = meet; }
};

