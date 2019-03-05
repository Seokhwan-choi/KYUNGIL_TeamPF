#pragma once
#include "GameObject.h"
//ĳ���� ����â ����
class choiceUi :
	public GameObject
{
private:
	//========================================================
	// ĳ���� ���� â �� ������ ���� 
	//========================================================
	
	//========================================================
	// ĳ���� ���� â ���� ���� 
	//========================================================
	RECT gameStartRc[5];	//�簢�� 5�� (4�� : ���̴� ��Ʈ 1�� : �Ⱥ��̴� ��Ʈ)
	RECT characterRc[4];	//ĳ���� 4�� ����
	RECT door[4];			//�ö󰡴� �� ������ֱ�
	POINT _center;			//�������ε�����  ������ ��Ʈ
	
	bool _doorUp;			//ó�� �ø� �� �Ұ��ֱ�
	bool _isCheck[4];		//ĳ���͸� �����ֱ� ���� �Ұ�
	bool _goUp[4];			//������ ĳ���͸� �����ֱ� ���� ����â�ø���  ���� �Ұ�
	bool _isShow;			//������°�?
	
	int _a;					//Ư�� true���� ��� ���� ����
	int _count;				//ī���� ++
	int _time;				//���ѽð�

	//========================================================
	// ĳ���� ���� â �̹��� ����
	//========================================================
	image* _timeImage;		//���ѽð� �̹��� �����ϱ�
	image* _background;		//��׶��� �̹��� �����ϱ�
	image* _doorImage;		//�� �̹���
	image* _characterImage[4];		//ĳ���� ��� �̹���

public:
	choiceUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~choiceUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

