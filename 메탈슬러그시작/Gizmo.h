#pragma once
#include "SingletonBase.h"
/****************************************************
## Gizmo ## 2019.02.05 
여기저기서 편하게 디버깅용 렌더링을 하고 싶을 때 사용

이것저것 수정해서 더 편하게 쓸 수 있도록. . . .
*****************************************************/
#define DefaultPenStroke 2	//기본 선 굵기
class Gizmo : public SingletonBase<Gizmo>
{
public:
	//기본 컬러들 
	enum class DefaultColor
	{
		Red, Green, Blue, Gray, White, Black, Null
	};
private:
	//맵순회할 이터레이터들 
	typedef map<DefaultColor, HBRUSH>::iterator BrushIter;
	typedef map<DefaultColor, HPEN>::iterator PenIter;
private:
	//기본 브러쉬 리스트 
	map<DefaultColor, HBRUSH> brushList;
	//기본 펜 리스트 
	map<DefaultColor, HPEN> penList; 
public:
	Gizmo();
	~Gizmo();
private:
	//기본 브러쉬 생성
	void CreateDefaultBrush(DefaultColor type, COLORREF color);
	//기본 펜 생성
	void CreateDefaultPen(DefaultColor type, COLORREF color);
public:
	//속이 빈 사각형을 렌더링 해준다. 
	void DrawNullRectangle(HDC hdc,RECT rc, DefaultColor color);
	//속이 꽉찬 사각형 렌더링
	void DrawFillRectangle(HDC hdc, RECT rc, DefaultColor color);
	//속이 비어있는 원을 그린다. 
	void DrawNullEllipse(HDC hdc, POINT center, int radius, DefaultColor color);
	//속이 꽉찬 원을 그린다.
	void DrawFillEllipse(HDC hdc, POINT center, int radius, DefaultColor color);
	//라인 렌더링
	void DrawLine(HDC hdc, POINT start, POINT end, DefaultColor color);
};

