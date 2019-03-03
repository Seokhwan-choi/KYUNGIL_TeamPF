#include "stdafx.h"
#include "KeyManager.h"

//키매니져 초기화
HRESULT KeyManager::init()
{
	//키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}
	return S_OK;//무조건 OK로 받는다.
}

//키매니져 해제		//추가롤 무언가를 생성했을 경우에 해재한다.
void KeyManager::release(void)
{
	
}

//키가 한번만 눌렸냐?
bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) //0x8000 컴퓨터만의 규칙? 규약? 한번 클릭했을경우에 나오는 값을 입력한 것임. &<-비트연산자. or , and
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


//키가 한번눌렸다 띄었냐?
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


//키가 계속 눌려있냐?
bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}


//토글키냐?
bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}

