#pragma once
#include "GameObject.h"
class GameCompleteUi : public GameObject
{
private:
	//========================================================
	//�̹��� ��Ʈ 
	//========================================================
	RECT completeRc[17];			//���� mission1	
	POINTFLOAT _wh;			    //�ʺ����
	POINTFLOAT _site[17];		//��ġ
	POINTFLOAT _y;				//y��ġ ����� ����

	//========================================================
	//�������� ���� ����
	//========================================================
	float _angle;				//��Ʈ �ޱ� ��
	float _speed;			   //������ ��Ʈ ���ǵ�
	int _count;				   //�� �ʵڿ� �����̰� �� ���̴�
	bool _isMove;			   //���� ������� �����̳�?
	
						
	image* _textImg[17];	   //�̼�1���ø�Ʈ!�̹���


public:
	GameCompleteUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~GameCompleteUi();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

