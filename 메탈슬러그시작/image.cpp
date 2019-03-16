#include "stdafx.h"
#include "image.h"
#pragma comment (lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_isTrans(FALSE),
	_blendImage(NULL),
	_stretchImage(NULL)
{
}
image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 세팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 세팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::initForStretchBlt()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->resID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	//알파블렌드 이미지 정보가 있다면
	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_blendImage);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->width, _imageInfo->height);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;


	if (_isTrans)//배경색 없애고 출력
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사할 좌표 시작점 x
			destY,					//복사할 좌표 시작점 y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(마젠타)
	}
	else //원본 이미지 그대로 출력
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{


	if (_isTrans)//배경색 없애고 출력
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사할 좌표 시작점 x
			destY,					//복사할 좌표 시작점 y
			sourWidth,				//복사될 이미지 가로크기
			sourHeight,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,			//복사 시작지점
			sourWidth,				//복사 영역 가로크기
			sourHeight,				//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(마젠타)
	}
	else //원본 이미지 그대로 출력
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	RECT renderRect = RectMake(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;


	//알파블렌딩 처음 사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 HDC의 내용을 -> 블렌드이미지에 복사
		//2. 메모리 DC의 배경색을 없앤후 다시 블렌드이미지에 복사
		//3. 블렌드이미지를 화면 HDC에 복사한다(알파블렌드)

		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);


		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사할 좌표 시작점 x
			0,						//복사할 좌표 시작점 y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(마젠타)

		//알파블렌딩
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 출력
	{
		//원본 이미지 그래도 알파블렌딩 할꺼냐?
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->width, _imageInfo->height);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;
	//알파블렌딩 처음 사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 HDC의 내용을 -> 블렌드이미지에 복사
		//2. 메모리 DC의 배경색을 없앤후 다시 블렌드이미지에 복사
		//3. 블렌드이미지를 화면 HDC에 복사한다(알파블렌드)

		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);


		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사할 좌표 시작점 x
			0,						//복사할 좌표 시작점 y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(마젠타)

		//알파블렌딩
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 출력
	{
		//원본 이미지 그래도 알파블렌딩 할꺼냐?
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{

	//알파블렌딩 처음 사용하냐?
//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 HDC의 내용을 -> 블렌드이미지에 복사
		//2. 메모리 DC의 배경색을 없앤후 다시 블렌드이미지에 복사
		//3. 블렌드이미지를 화면 HDC에 복사한다(알파블렌드)

		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, sourX, sourY, SRCCOPY);


		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,   //복사할 장소의 DC
			0,                 //복사할 좌표 시작점 x
			0,                 //복사할 좌표 시작점 y
			_imageInfo->width,      //복사될 이미지 가로크기
			_imageInfo->height,     //복사될 이미지 세로크기
			_imageInfo->hMemDC,      //복사될 대상 DC
			sourX, sourY,               //복사 시작지점
			_imageInfo->width,      //복사 영역 가로크기
			_imageInfo->height,      //복사 영역 세로크기
			_transColor);         //복사할때 제외할 색상(마젠타)

		 //알파블렌딩
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //원본 이미지 그대로 출력
	{
		//원본 이미지 그대도 알파블렌딩 할꺼냐?
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC
			destX,						//복사될 좌표 시작점 X
			destY,						//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,		//복사될 이미지 가로크기
			_imageInfo->frameHeight,	//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);				//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;
	//이미지 예외처리
	//int hp;
	//if (hp < 0) hp = 0;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC
			destX,						//복사될 좌표 시작점 X
			destY,						//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,		//복사될 이미지 가로크기
			_imageInfo->frameHeight,	//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);				//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentframeX, int currentframeY, int alpha)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;
	//RECT renderRC = RectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	//if (renderRC.right < 0 || renderRC.left > WINSIZEX || renderRC.top > WINSIZEY || renderRC.bottom < 0)
	//	return;

	if (!_blendImage) this->initForAlphaBlend();

	_imageInfo->currentFrameX = currentframeX;
	_imageInfo->currentFrameY = currentframeY;

	//알파값 ( 0 - 255 ) 수가 클수록 선명하다.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC,
			0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth
			, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(알파렌더-이미지잘라서붙이기)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void image::stretchRender(HDC hdc, int destX, int destY, float scale)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->width * scale, _imageInfo->height * scale);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;
	//스트레치이미지 처음 사용하냐?
	//이미지 스케일링을 사용할 수 있도록 초기화 해라
	if (!_stretchImage) this->initForStretchBlt();

	_stretchImage->width = _imageInfo->width * scale;
	_stretchImage->height = _imageInfo->height * scale;

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		StretchBlt(hdc, destX, destY, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	RECT renderRect = RectMake(destX, destY, _imageInfo->frameWidth* scale, _imageInfo->frameHeight * scale);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.bottom < 0 || renderRect.top > WINSIZEY)
		return;
	//스트레치이미지 처음 사용하냐?
	//이미지 스케일링을 사용할 수 있도록 초기화 해라
	if (!_stretchImage) this->initForStretchBlt();

	_stretchImage->width = _imageInfo->width * scale;
	_stretchImage->height = _imageInfo->height * scale;
	_stretchImage->frameWidth = _stretchImage->width / (_imageInfo->maxFrameX + 1);
	_stretchImage->frameHeight = _stretchImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,							//복사할 장소의 DC
			destX,							//복사될 좌표 시작점 X
			destY,							//복사될 좌표 시작점 Y
			_stretchImage->frameWidth,		//복사될 이미지 가로크기
			_stretchImage->frameHeight,		//복사될 이미지 세로크기
			_stretchImage->hMemDC,			//복사될 대상 DC
			0, 0,							//복사 시작지점
			_stretchImage->frameWidth,		//복사 영역 가로크기
			_stretchImage->frameHeight,		//복사 영역 세로크기
			_transColor);					//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		StretchBlt(hdc, destX, destY, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}
