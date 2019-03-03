#pragma once


//==========================================================================//
//						## CommomMacroFuntion ##							//
//==========================================================================//
#define PI 3.14159265359f

//==========================================================================//
//						## 사각형 가로세로 만들기 ##							//
//==========================================================================//
//----가로----/
inline LONG getWidth(RECT rc)
{
	return rc.right - rc.left;
}
//----세로----/
inline LONG getHeight(RECT rc)
{
	return rc.bottom - rc.top;
}

//==========================================================================//
//								## POINT ##									//
//==========================================================================//
inline POINT PointMake(int x, int y)  //매크로 함수보다 명시적이고 눈에 잘 보인다.
{
	POINT pt = { x, y };
}

//==========================================================================//
//								## 선그리기 ##								//
//==========================================================================//
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//==========================================================================//
//								## RECT만들기 ##								//
//==========================================================================//
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//==========================================================================//
//							## RECT중심좌표 만들기 ##							//
//==========================================================================//
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width/2, y + height/2 };
	return rc;
}

//==========================================================================//
//							## RECT바텀좌표 만들기 ##							//
//==========================================================================//
inline RECT RectMakeBottom(int x, int y, int width, int height) 
{
	RECT rc = { x - (width / 2), y - height, y + (width / 2), y };
	return rc;
}

//==========================================================================//
//						## 렉탱글함수 이용해서 그리기 ##						//
//==========================================================================//
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//==========================================================================//
//							## 렉탱글함수 요약하기. ##							//
//==========================================================================//
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//==========================================================================//
//						## 일립스함수 이용해서 타원그리기 ##						//
//==========================================================================//
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//==========================================================================//
//						## 일립스함수 이용해서 타원그리기 ##						//
//==========================================================================//
inline void EllipseCenter(HDC hdc, int x, int y, int width, int height)
{ 
	Ellipse(hdc, x - width / 02, y - height / 02, x + width, y + height/0200);
}
//==========================================================================//
//							## 일립스함수 요약하기 ##							//
//==========================================================================//
inline void EllipseCenter(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


//==========================================================================//
//						## 점이 사각형 안인지 체크 ##							//
//==========================================================================//
inline bool isptinRect(RECT rc, float ptx, float pty)
{
	if ((rc.left <= ptx && ptx <= rc.right) && (rc.top <= pty && pty <= rc.bottom))
	{
		return true;
	}
	else return false;
}
//==========================================================================//
//						## 점이 원의 안인지 체크 ##							//
//==========================================================================//
inline bool isptinEllipse(RECT rc, float radius, float ptx, float pty)
{
	float deltaX = (rc.left + getWidth(rc) / 2) - ptx;
	float deltaY = (rc.top + getHeight(rc) / 2) - pty;
	float length = sqrt(deltaX*deltaX + deltaY * deltaY);
	if (length > radius)
	{
		return false;
	}
	return true;
}

//==========================================================================//
//						## 점과 점 사이의 직선거리 ##							//
//==========================================================================//
inline float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float distance = sqrtf((x * x) + (y * y));

	return  distance;
}

//==========================================================================//
//						## 두 점사이의 삼각비 공식 ##							//
//==========================================================================//
inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;										
	float y = y2 - y1;										

	float distance = sqrtf((x * x) + (y * y));				

	float angle = acos(x / distance);						

	if (y2 > y1)											
	{
		angle = PI * 2.0f - angle;							
		if (angle >= PI * 2.0f)								
			angle -= PI * 2.0f;								
	}

	return angle;											
}
//==========================================================================//
//							##	사각형 교환	##								//
//==========================================================================//
inline void SwapRect(RECT& rc1, RECT& rc2)
{
	RECT temp;
	temp = rc1;
	rc1 = rc2;
	rc2 = temp;
}


//==========================================================================//
//						## 원 사각형 충돌 매크로 ##							//
//==========================================================================//
inline bool Ellipse_Rect_Collision(RECT round, RECT rc)
{
	int x = (int)round.left + (int)getWidth(round) / 2;
	int y = (int)round.top + (int)getHeight(round) / 2;
	int nRadius = (int)getWidth(round) / 2;

	if ((rc.left <= x && x <= rc.right) ||
		(rc.top <= y && y <= rc.bottom))
	{
		RECT rcEX = { rc.left - nRadius,rc.top - nRadius,rc.right + nRadius,rc.bottom + nRadius };

		if ((rcEX.left < x && x < rcEX.right) &&
			(rcEX.top < y && y < rcEX.bottom)) {
			return true;
		}
	}
	else
	{
		if (isptinEllipse(round, (float)nRadius, (float)rc.left, (float)rc.top)) return true;
		if (isptinEllipse(round, (float)nRadius, (float)rc.left, (float)rc.bottom)) return true;
		if (isptinEllipse(round, (float)nRadius, (float)rc.right, (float)rc.top)) return true;
		if (isptinEllipse(round, (float)nRadius, (float)rc.right, (float)rc.bottom)) return true;
	}
	return false;
}
//==========================================================================//
//						## 원과 선의 충돌 매크로 ##							//
//==========================================================================//
inline bool Rect_Horizon_Collision(RECT round, float pty)
{
	int nCentery = (int)round.top + (int)getHeight(round) / 2;
	int nRadius = (int)getWidth(round) / 2;

	if (pty + nRadius >= nCentery && pty - nRadius <= nCentery) return true;
	return false;
}
//==========================================================================//
//						## 디그리를 라디안으로 변환 ##						//
//==========================================================================//
inline float DegreeToRadian(float degree)
{
	return degree * 3.14159265f / 180.0f;
}
//==========================================================================//
//						## 라디안을 디그리로 변환 ##							//
//==========================================================================//
inline float RadianToDegree(float radian)
{
	return radian * 180.0f / 6.14159265f;
}


//==========================================================================//
//							## 원 원 충돌 매크로 ##							//
//==========================================================================//
inline bool Ellipse_Ellipse_Collision(RECT round1, RECT round2)
{
	float c1x = (float)round1.left + (float)getWidth(round1) / 2;
	float c1y = (float)round1.top + (float)getHeight(round1) / 2;
	float c2x = (float)round2.left + (float)getWidth(round2) / 2;
	float c2y = (float)round2.top + (float)getHeight(round2) / 2;
	float deltaX = c1x - c2x;
	float deltaY = c1y - c2y;
	float length = sqrt(deltaX*deltaX + deltaY * deltaY);

	if (length > ((float)getWidth(round1) / 2 + (float)getWidth(round2) / 2)) return false;

	return true;
}