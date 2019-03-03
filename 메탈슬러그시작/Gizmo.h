#pragma once
#include "SingletonBase.h"
/****************************************************
## Gizmo ## 2019.02.05 
�������⼭ ���ϰ� ������ �������� �ϰ� ���� �� ���

�̰����� �����ؼ� �� ���ϰ� �� �� �ֵ���. . . .
*****************************************************/
#define DefaultPenStroke 2	//�⺻ �� ����
class Gizmo : public SingletonBase<Gizmo>
{
public:
	//�⺻ �÷��� 
	enum class DefaultColor
	{
		Red, Green, Blue, Gray, White, Black, Null
	};
private:
	//�ʼ�ȸ�� ���ͷ����͵� 
	typedef map<DefaultColor, HBRUSH>::iterator BrushIter;
	typedef map<DefaultColor, HPEN>::iterator PenIter;
private:
	//�⺻ �귯�� ����Ʈ 
	map<DefaultColor, HBRUSH> brushList;
	//�⺻ �� ����Ʈ 
	map<DefaultColor, HPEN> penList; 
public:
	Gizmo();
	~Gizmo();
private:
	//�⺻ �귯�� ����
	void CreateDefaultBrush(DefaultColor type, COLORREF color);
	//�⺻ �� ����
	void CreateDefaultPen(DefaultColor type, COLORREF color);
public:
	//���� �� �簢���� ������ ���ش�. 
	void DrawNullRectangle(HDC hdc,RECT rc, DefaultColor color);
	//���� ���� �簢�� ������
	void DrawFillRectangle(HDC hdc, RECT rc, DefaultColor color);
	//���� ����ִ� ���� �׸���. 
	void DrawNullEllipse(HDC hdc, POINT center, int radius, DefaultColor color);
	//���� ���� ���� �׸���.
	void DrawFillEllipse(HDC hdc, POINT center, int radius, DefaultColor color);
	//���� ������
	void DrawLine(HDC hdc, POINT start, POINT end, DefaultColor color);
};

