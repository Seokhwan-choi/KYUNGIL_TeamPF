#include "stdafx.h"
#include "totalScore.h"
#include "playerDataUi.h"

totalScore::totalScore(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//���� ���� ���� ��Ʈ ����
	_ScoreRc = RectMake(272,444,66,68);
	//���� ���� ��������
	_saveRc = RectMake(272,342,66,66);
	//���� ����
	_milRc = RectMake(427,373,161,35);
	//���� �̹���
	_imgRc = RectMake(98,250,124,160);
	//������ Ʋ
	_frameRc = RectMake(78,214,555,665);
	//���� ��Ʈ
	_xRc = RectMake(409, 380, 24, 24);
	//�̸� ��Ʈ
	_nameRc = RectMake(110, 616, 442, 228);
	IMAGEMANAGER->findImage("����Ʋ");
	IMAGEMANAGER->findImage("������̸�");
	IMAGEMANAGER->findImage("���ο�����");
	IMAGEMANAGER->findImage("x");
	IMAGEMANAGER->findImage("��");
	IMAGEMANAGER->findImage("�������μ�");
	

	//������ �̹��� ���� ���� �ʱ�ȭ
	_index =13;
	_count = 0;

	//���Ѽ��� �ʱ�ȭ
	_saveNum = 0;
	_isSave = true;
}

totalScore::~totalScore()
{
}

HRESULT totalScore::Init()
{
	return S_OK;
}

void totalScore::Release()
{
}

void totalScore::Update()
{
	_count++;
	//���� �ִϸ��̼�
	IMAGEMANAGER->findImage("���ο�����")->setFrameY(0);
	if (_count % 8 == 0) {
		_index--;
		if (_index < 3) {
			_index = 3;
		}
		IMAGEMANAGER->findImage("���ο�����")->setFrameX(_index);
	}
	//���� ���μ� 1�� �÷��ִ� ó��	
	if (_isSave == true) {
		for (int i = 0; i < DATA->getCaptive(); i++) {
			if (_count % 50 == 0) {
				_saveNum += 1;
				DATA->setScore(_saveNum * 10000);
				if (_saveNum == DATA->getCaptive()) {
					_isSave = false;
					break;
				}
			}
			break;
		}
	}
	//�ϳ��� �÷���������
	if (DATA->getCaptive() > 0) {
		((playerDataUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "playerdataui"))->setRect({ 300.f,WINSIZEY / 2 });
	}

	//5�� ��  �ٽ� ����ȭ�����ε����ش�
	//if (_count == 1000) {
	//	DATA->Init();
	//	SCENEMANAGER->ChangeScene("����ȭ��");
	//}


}

void totalScore::Render()
{
	//�̹��� ����
	IMAGEMANAGER->frameRender("���ο�����", getMemDC(), _imgRc.left, _imgRc.top);
	IMAGEMANAGER->render("����Ʋ", getMemDC(), _frameRc.left, _frameRc.top);
	IMAGEMANAGER->render("������̸�", getMemDC(), _nameRc.left, _nameRc.top);
	IMAGEMANAGER->render("x", getMemDC(), _xRc.left, _xRc.top);
	IMAGEMANAGER->render("��", getMemDC(), _milRc.left, _milRc.top);
	
	//1�ʾ� 1�� �÷��ֵ��� �Ѵ�
	if (DATA->getCaptive() < 10) {
		IMAGEMANAGER->frameRender("�������μ�",getMemDC(), _saveRc.left, _saveRc.top,0,0);
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _saveRc.left + 66, _saveRc.top,_saveNum, 0);
	}
	
	//�������μ� �ջ��� �� ���� �÷��ֱ�
	int _num = 66;
	if (DATA->getCaptive() < 10) {
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _ScoreRc.left, _ScoreRc.top, _saveNum, 0);
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _ScoreRc.left + _num, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _ScoreRc.left + _num*2, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _ScoreRc.left + _num * 3, _ScoreRc.top, 0, 0);
		IMAGEMANAGER->frameRender("�������μ�", getMemDC(), _ScoreRc.left + _num * 4, _ScoreRc.top, 0, 0);
	}

	
}
