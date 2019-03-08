#pragma once
//=============================================================
//	## image ## (앞으로 계속 업데이트 된다)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스로 로딩
		LOAD_FILE,			//파일로 로딩
		LOAD_EMPTY,			//빈비트맵으로 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//리소스 ID
		HDC			hMemDC;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드비트맵
		float		x;				//이미지 x좌표
		float		y;				//이미지 y좌표
		int			width;			//이미지 가로크기
		int			height;			//이미지 세로크기
		int			currentFrameX;	//현재 프레임X
		int			currentFrameY;	//현재 프레임Y
		int			maxFrameX;		//최대 X프레임 갯수
		int			maxFrameY;		//최대 Y프레임 갯수
		int			frameWidth;		//1프레임 가로길이
		int			frameHeight;	//1프레임 세로길이
		BYTE		loadType;		//이미지 로드타입

		tagImage()	//생성자 = 초기화
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨거냐?
	COLORREF		_transColor;	//배경색 없앨 RGB색상 (마젠타 = RGB(255, 0, 255))

	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능

	LPIMAGE_INFO	_stretchImage;	//스트레치이미지

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화
	HRESULT init(DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일 초기화(주사용)
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일 초기화(주사용)
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	//알파블렌드 초기화
	HRESULT initForAlphaBlend();
	//스트레치렌더 초기화
	HRESULT initForStretchBlt();

	//해제
	void release();

	//=============================================================
	//	## 일반렌더 ##
	//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//=============================================================
	//	## 알파렌더 ##
	//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//=============================================================
	//	## 프레임렌더 ##
	//=============================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//=============================================================
	//	## 루프렌더 ##
	//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//=============================================================
	//	## 스트레치렌더 ## (이미지 스케일링)
	//=============================================================
	void stretchRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	//=============================================================
	//	## 인라인함수 ## (캡슐화 - 겟터, 셋터)
	//=============================================================
		//DC 얻기
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//이미지 x좌표
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//이미지 y좌표
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }
	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	//바운딩 박스(충돌용 렉트)
	inline RECT boudingBox()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}
	inline RECT boudingBoxWithFrame()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//프레임 X
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 1프레임의 가로, 세로크기
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//맥스프레임 X, Y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

};
