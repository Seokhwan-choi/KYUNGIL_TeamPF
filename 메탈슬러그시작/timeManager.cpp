#include "stdafx.h"
#include "timeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime�Լ��� ����ϱ� ���ؼ�
//�����찡 ���۵ǰ� �� �� �ð��� ���Ͻ����ش�
//GetTickCount���� ������ �ɿ���~ �� ����

HRESULT timeManager::init(void)
{
	//���� Ÿ�̸� �������� üũ
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//���� Ÿ�̸Ӹ� �����ϴϱ�
		_isHardware = true;
		//�ʴ� �ð� ���(1�� ��� ī���� �ϳ�)
		_timeScale = 1.0f / _periodFrequency;
		//�ʱ�ȭ ������ �ð��� ������ �ð�����
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �����ϱ�
		_isHardware = false;
		_timeScale = 1.0f / 1000.0f;
		_lastTime = timeGetTime();
	}

	//������ �ʱ�ȭ
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0;

	return S_OK;
}

void timeManager::release(void)
{
}

void timeManager::update(float lockFPS)
{
	if (_isHardware)
	{
		//����ð� ���
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
		_curTime = timeGetTime();
	}

	//�������� ������ �� ���
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//������ ��Ű��
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware)
			{
				//����ð� ���
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else
			{
				//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
				_curTime = timeGetTime();
			}
			//�������� ������ �� ���
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//���� �ð� ����
	_lastTime = _curTime;
	//������ �� ����
	_FPSTimeElapsed += _timeElapsed;
	//������ �ð� ����
	_worldTime += _timeElapsed;

	//������ �ʱ�ȭ�� 1�ʸ��� �����ϱ�
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

	_FPSFrameCount++;
}

void timeManager::render(HDC hdc)
{
	char str[256];
	//���ڹ����
	SetBkMode(hdc, TRANSPARENT);
	//���ڻ���
	SetTextColor(hdc, RGB(0, 255, 0));

	//FPS
	sprintf(str, "FPS: %d", _frameRate);
	TextOut(hdc, 0, 0, str, strlen(str));
	//��ü�ð�
	sprintf(str, "WorldTime: %.2f", _worldTime);
	TextOut(hdc, 0, 20, str, strlen(str));
	//�������Ӵ� ����ð�
	sprintf(str, "ElapsedTime: %.4f", _timeElapsed);
	TextOut(hdc, 0, 40, str, strlen(str));
}