#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImageKey, const char * backImageKey, int x, int y, int width, int height)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = width;
	_height = height;
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];
	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp�� �����
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);
	
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render(void)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y);
	//�տ� �������� ü�¹� �̹���
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}
