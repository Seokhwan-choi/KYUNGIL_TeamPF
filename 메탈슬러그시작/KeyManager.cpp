#include "stdafx.h"
#include "KeyManager.h"

//Ű�Ŵ��� �ʱ�ȭ
HRESULT KeyManager::init()
{
	//Ű���� ���� �������� ���� ���·� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}
	return S_OK;//������ OK�� �޴´�.
}

//Ű�Ŵ��� ����		//�߰��� ���𰡸� �������� ��쿡 �����Ѵ�.
void KeyManager::release(void)
{
	
}

//Ű�� �ѹ��� ���ȳ�?
bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) //0x8000 ��ǻ�͸��� ��Ģ? �Ծ�? �ѹ� Ŭ��������쿡 ������ ���� �Է��� ����. &<-��Ʈ������. or , and
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}
	return false;
}


//Ű�� �ѹ����ȴ� �����?
bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;

	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}
	return false;
}


//Ű�� ��� �����ֳ�?
bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}


//���Ű��?
bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}

