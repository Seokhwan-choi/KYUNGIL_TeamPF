#pragma once
#include "GameObject.h"
class Rect : public GameObject
{
private:

	int _count;				//��� ����� ��(���ѽð� ���߱� ���� ����)
	int _playTime;			//���ѽð�
	int _score;				//����
	int _life;				//���
	int _bomb;				//����ź����
	int _arms;				//��ź���� ->enum�������ؼ� �Ϲ����ϋ� �������� ǥ��
							//���ӽ��϶� 200���� ǥ���ϵ��� ��
	image* _scoreImage;
	image* _timeImage;
	image* _lifeImage;
	image* _bombImage;
	image* _armsImage;
	image* _insertcoinImage;


public:
	
	Rect(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Rect();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

