#pragma once
#include "image.h"

//백버퍼 이미지를 이미지매니져에 담아두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;			//화면 HDC
	bool _managerInit;	//매니져 초기화 했냐?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 이미지 얻기
	image* getBackBuffer() { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//화면 DC 얻기
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};
