#include "stdafx.h"
#include "Gizmo.h"

/***************************************************************************
## Gizmo ##  
�⺻ �귯���� ���� ���� 
****************************************************************************/
Gizmo::Gizmo()
{
	this->CreateDefaultBrush(DefaultColor::Red, RGB(255, 0, 0));
	this->CreateDefaultBrush(DefaultColor::Green, RGB(0, 255, 0));
	this->CreateDefaultBrush(DefaultColor::Blue, RGB(0, 0, 255));
	this->CreateDefaultBrush(DefaultColor::Gray, RGB(100, 100, 100));
	this->CreateDefaultBrush(DefaultColor::White, RGB(255, 255, 255));
	this->CreateDefaultBrush(DefaultColor::Black, RGB(0, 0, 0));
	//NULL_BRUSH�� GetStockObject�Լ��� ���ؼ��� ���������ϹǷ� ���� ���� 
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
�⺻ �귯���� ���� ���� 
****************************************************************************/
Gizmo::~Gizmo()
{
	//�ݺ��ڴ� ���� ������������ 
	PenIter penIter = this->penList.begin();
	//���� ���� �ƴҶ����� ��ȸ 
	for (; penIter != penList.end(); ++penIter)
	{
		//�⺻ �� ���� 
		DeleteObject(penIter->second);
	}
	//���������� ���� ������ ����ش�
	penList.clear();
	//�귯�� �ݺ��ڵ� ���������� �귯�� ���� ���������� 
	BrushIter brushIter = this->brushList.begin();
	//���� �ƴҶ� ���� ��ȸ�ϰ�
	for (; brushIter != brushList.end(); ++brushIter)
	{
		//�⺻ �귯�� ���� 
		DeleteObject(brushIter->second);
	}
	//���������� ���� ����ش�
	brushList.clear();
}


/***************************************************************************
## CreateDefaultBrsuh ##
@@ DefaultColor type : �귯�� ���� enum�� 
@@ COLORREF color : ������ �⺻ �귯�� ���� 
****************************************************************************/
void Gizmo::CreateDefaultBrush(DefaultColor type, COLORREF color)
{
	//�ʿ� �̹� �ش� �÷��� �귯���� �����Ǿ� �ִ��� �˻� 
	BrushIter iter = this->brushList.find(type);
	//���� ���� ���� �ƴ϶�� ã�Ҵٴ� �� == �̹� ������ �귯���� �ִٴ� ��
	if (iter != brushList.end())
	{
		//�׷��Ƿ� �Ʒ��� ������ ���� ��Ű�� ���� �Լ��� ���������� 
		return;
	}
	//�귯�� ���� 
	HBRUSH brush = (HBRUSH)CreateSolidBrush(color);
	//�ʿ� ��´�
	this->brushList.insert(make_pair(type, brush));
}

/***************************************************************************
## CreateDefaultPen ##
@@ DefaultColor type : �⺻ �귯�� Ÿ��(���� enum��)
@@ COLORREF color : ������ �� ���� 
****************************************************************************/
void Gizmo::CreateDefaultPen(DefaultColor type, COLORREF color)
{
	//�ʿ� �̹� �ش� �÷��� ���� �����Ǿ� �ִ��� �˻� 
	PenIter iter = this->penList.find(type);
	//���� ���� ���� �ƴ϶�� ã�Ҵٴ� �� == �̹� ������ ���� �ִٴ� ��
	if (iter != penList.end())
	{
		//�׷��Ƿ� �Ʒ��� ������ ���� ��Ű�� ���� �Լ��� ���������� 
		return;
	}
	//�����
	//CreatePen(�� Ÿ��, �⺻ �汽��, ����) 
	HPEN pen = (HPEN)CreatePen(PS_SOLID, DefaultPenStroke, color);
	//������ �� �ʿ� ���
	this->penList.insert(make_pair(type, pen));
}

/***************************************************************************
## DrawNullRectangle ##
���� ����ִ� �簢���� �׷��ش�. 

@@ HDC hdc : �׸� ���� 
@@ RECT rc : �׷��� ��Ʈ 
@@ DefaultColor color : �⺻ ���� 
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
���� ä���� �ִ� �簢���� �׷��ش�. 

@@ HDC hdc : �׸� ����
@@ RECT rc : �׷��� ��Ʈ
@@ DefaultColor color : �⺻ ����
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
���� ����� �ִ� ���� �׷��ش�.

@@ HDC hdc : �׸� ����
@@ POINT center : �߽���ǥ
@@ int radius : ������ 
@@ DefaultColor color : �⺻ ����
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
���� ���� ���� �׸���

@@ HDC hdc : �׸� ����
@@ POINT center : �߽���ǥ
@@ int radius : ������
@@ DefaultColor color : �⺻ ����
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
������ �׷��ش�. 

@@ HDC hdc : �׸� ����
@@ POINT start : ������
@@ POINT end : ���� 
@@ DefaultColor color : �⺻ ����
****************************************************************************/
void Gizmo::DrawLine(HDC hdc, POINT start, POINT end, DefaultColor color)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, this->penList[color]);

	MoveToEx(hdc, (int)start.x, (int)start.y, NULL);
	LineTo(hdc, (int)end.x, (int)end.y);

	SelectObject(hdc, oldPen);
}
