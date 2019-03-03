#pragma once
#include "SingletonBase.h"

//==========================================================================//
//						## Key Manager ## Ű�Ŵ���							//
//==========================================================================//
#define KEYMAX 256


class KeyManager :	public SingletonBase<KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:

	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init();

	//Ű�Ŵ��� ����
	void release(void);
	
	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);

	//Ű�� �ѹ����ȴ� �����?
	bool isOnceKeyUp(int key);

	//Ű�� ��� �����ֳ�?
	bool isStayKeyDown(int key);

	//���Ű��?
	bool isToggleKey(int key);



	KeyManager() {}
	~KeyManager() {}
};

