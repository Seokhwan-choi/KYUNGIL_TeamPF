#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	RECT gameStartRc[5];	//�簢�� 5�� �����ϱ�
	POINT _center;			//�������ε����� ������ ��Ʈ ����Ʈ ����
	bool _isCheck[4];		//goUp �ε��� �����ϱ� ���� �Ұ�����
	bool _goUp[4];			//�ε��� �ϳ� �����ؼ� �ϳ��� ��Ʈ �ø����� ������ �Ұ�����
	bool _isShow;			//ĳ���� ������°� �������ִ� �Լ�
	int a;					//i�� �ֱ����ؼ� ������ ���� ����
	int _time;
	int _mainSceneTime;		//ĳ���ͼ��� ���� �ð�
	
	
public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();

	HRESULT Init();
	void Release();
	void Update();
	void Render();	
};

