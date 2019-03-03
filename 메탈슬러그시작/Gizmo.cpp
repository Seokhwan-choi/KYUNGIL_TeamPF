#include "stdafx.h"
#include "Gizmo.h"

/***************************************************************************
## Gizmo ##  
기본 브러쉬들 전부 생성 
****************************************************************************/
Gizmo::Gizmo()
{
	this->CreateDefaultBrush(DefaultColor::Red, RGB(255, 0, 0));
	this->CreateDefaultBrush(DefaultColor::Green, RGB(0, 255, 0));
	this->CreateDefaultBrush(DefaultColor::Blue, RGB(0, 0, 255));
	this->CreateDefaultBrush(DefaultColor::Gray, RGB(100, 100, 100));
	this->CreateDefaultBrush(DefaultColor::White, RGB(255, 255, 255));
	this->CreateDefaultBrush(DefaultColor::Black, RGB(0, 0, 0));
	//NULL_BRUSH는 GetStockObject함수를 통해서만 생성가능하므로 별도 생성 
	HBRUSH nullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	this->brushList.insert(make_pair(DefaultColor::Null, nullBrush));

	this->CreateDefaultPen(DefaultColor::Red, RGB(255, 0, 0));
	this->CreateDefaultPen(DefaultColor::Green, RGB(0, 255, 0));
	this->CreateDefaultPen(DefaultColor::Blue, RGB(0, 0, 255));
	this->CreateDefaultPen(DefaultColor::Gray, RGB(100, 100, 100));
	this->CreateDefaultPen(DefaultColor::White, RGB(255, 255, 255));
	this->CreateDefaultPen(DefaultColor::Black, RGB(0, 0, 0));
	HPEN nullPen = (HPEN)GetStockObject(NULL_PEN);
	this->penList.insert(make_pair(DefaultColor::Null, nullPen));
}

/***************************************************************************
## ~Gizmo ##
기본 브러쉬들 전부 삭제 
****************************************************************************/
Gizmo::~Gizmo()
{
	//반복자는 맵의 시작지점부터 
	PenIter penIter = this->penList.begin();
	//맵의 끝이 아닐때까지 순회 
	for (; penIter != penList.end(); ++penIter)
	{
		//기본 펜 삭제 
		DeleteObject(penIter->second);
	}
	//다지웠으면 맵의 공간도 비워준다
	penList.clear();
	//브러쉬 반복자도 마찬가지로 브러쉬 맵의 시작점부터 
	BrushIter brushIter = this->brushList.begin();
	//끝이 아닐때 까지 순회하고
	for (; brushIter != brushList.end(); ++brushIter)
	{
		//기본 브러쉬 삭제 
		DeleteObject(brushIter->second);
	}
	//마찬가지로 공간 비워준다
	brushList.clear();
}


/***************************************************************************
## CreateDefaultBrsuh ##
@@ DefaultColor type : 브러쉬 색상 enum값 
@@ COLORREF color : 생성할 기본 브러쉬 색상 
****************************************************************************/
void Gizmo::CreateDefaultBrush(DefaultColor type, COLORREF color)
{
	//맵에 이미 해당 컬러의 브러쉬가 생성되어 있는지 검색 
	BrushIter iter = this->brushList.find(type);
	//만약 맵의 끝이 아니라면 찾았다는 뜻 == 이미 생성된 브러쉬가 있다는 뜻
	if (iter != brushList.end())
	{
		//그러므로 아래의 내용을 실행 시키지 말고 함수를 빠져나가자 
		return;
	}
	//브러쉬 생성 
	HBRUSH brush = (HBRUSH)CreateSolidBrush(color);
	//맵에 담는다
	this->brushList.insert(make_pair(type, brush));
}

/***************************************************************************
## CreateDefaultPen ##
@@ DefaultColor type : 기본 브러쉬 타입(색상 enum값)
@@ COLORREF color : 생성할 펜 색상 
****************************************************************************/
void Gizmo::CreateDefaultPen(DefaultColor type, COLORREF color)
{
	//맵에 이미 해당 컬러의 펜이 생성되어 있는지 검색 
	PenIter iter = this->penList.find(type);
	//만약 맵의 끝이 아니라면 찾았다는 뜻 == 이미 생성된 펜이 있다는 뜻
	if (iter != penList.end())
	{
		//그러므로 아래의 내용을 실행 시키지 말고 함수를 빠져나가자 
		return;
	}
	//펜생성
	//CreatePen(펜 타입, 기본 펜굵기, 색상) 
	HPEN pen = (HPEN)CreatePen(PS_SOLID, DefaultPenStroke, color);
	//생성한 펜 맵에 등록
	this->penList.insert(make_pair(type, pen));
}

/***************************************************************************
## DrawNullRectangle ##
속이 비어있는 사각형을 그려준다. 

@@ HDC hdc : 그릴 버퍼 
@@ RECT rc : 그려줄 렉트 
@@ DefaultColor color : 기본 색상 
****************************************************************************/
void Gizmo::DrawNullRectangle(HDC hdc, RECT rc, DefaultColor color)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brushList[DefaultColor::Null]);
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	Rectangle(hdc, rc);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

/***************************************************************************
## DrawFillRectangle ##
속이 채워져 있는 사각형을 그려준다. 

@@ HDC hdc : 그릴 버퍼
@@ RECT rc : 그려줄 렉트
@@ DefaultColor color : 기본 색상
****************************************************************************/
void Gizmo::DrawFillRectangle(HDC hdc,RECT rc, DefaultColor color)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brushList[color]);
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	Rectangle(hdc, rc);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

/***************************************************************************
## DrawNullEllipse ##
속이 비워져 있는 원을 그려준다.

@@ HDC hdc : 그릴 버퍼
@@ POINT center : 중심좌표
@@ int radius : 반지름 
@@ DefaultColor color : 기본 색상
****************************************************************************/
void Gizmo::DrawNullEllipse(HDC hdc, POINT center, int radius, DefaultColor color)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brushList[DefaultColor::Null]);
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	RECT rc = RectMakeCenter(center.x, center.y, radius, radius);
	Ellipse(hdc, rc.left,rc.top,rc.right,rc.bottom);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

/***************************************************************************
## DrawFillEllipse ##
속이 꽉찬 원을 그린다

@@ HDC hdc : 그릴 버퍼
@@ POINT center : 중심좌표
@@ int radius : 반지름
@@ DefaultColor color : 기본 색상
****************************************************************************/
void Gizmo::DrawFillEllipse(HDC hdc, POINT center, int radius, DefaultColor color)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brushList[color]);
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	RECT rc = RectMakeCenter(center.x, center.y, radius, radius);
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}


/***************************************************************************
## DrawLine ##
라인을 그려준다. 

@@ HDC hdc : 그릴 버퍼
@@ POINT start : 시작점
@@ POINT end : 끝점 
@@ DefaultColor color : 기본 색상
****************************************************************************/
void Gizmo::DrawLine(HDC hdc, POINT start, POINT end, DefaultColor color)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	MoveToEx(hdc, (int)start.x, (int)start.y, NULL);
	LineTo(hdc, (int)end.x, (int)end.y);

	SelectObject(hdc, oldPen);
}
