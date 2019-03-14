#pragma once
#include "GameObject.h"
class stage1StartUi : public GameObject
{
private:
	//========================================================
	//�̹��� ��Ʈ 
	//========================================================

	RECT startRc[14];			//���� mission1	
	POINTFLOAT _wh;			    //�ʺ����
	POINTFLOAT _site[14];		//��ġ
	POINTFLOAT _y;				//y��ġ ����� ����
	//========================================================
	//�������� ���� ����
	//========================================================
	float _angle;				//��Ʈ �ޱ� ��
	float _speed;			   //������ ��Ʈ ���ǵ�
	int _count;				   //�� �ʵڿ� �����̰� �� ���̴�
	bool _isMove;			   //���� ������� �����̳�?
	//�̹��� 
	image* _textImg[14];

public:
	stage1StartUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~stage1StartUi();

	POINTFLOAT* getSite() { return _site; }

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

