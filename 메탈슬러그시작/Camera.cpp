#include "stdafx.h"
#include "Camera.h"

// 카메라 위치를 세팅 해준다.
void Camera::SetCamera(POINTFLOAT pos)
{
	// 해당 타겟을 중심으로 카메라를 그려준다.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);


	//if (_cameraPos.x - WINSIZEX / 2 < 0)
	//{
	//	_cameraPos.x = WINSIZEX / 2;
	//}

	// 추가 예정
	// 추가적으로 카메라의 위치를 보정해줘야 한다.

	if (_cameraRect.left < 0)                   //맵을 안벗어나게 
	{
		_cameraPos.x = _cameraPos.x - _cameraRect.left;//이렇게 쓸수도있다  음수가되서 --되면+가되다는데?
		//_cameraPos.x = WINSIZEX / 2;       //난이게좋다 더
	}

	if (_cameraRect.bottom > 1050)
	{
		_cameraPos.y = _cameraPos.y - (_cameraRect.bottom - 1050); //1150 
	}

	if (_cameraRect.top < 0)
	{
		_cameraPos.y = _cameraPos.y - _cameraRect.top; 
	}

	//if (_cameraRect.top < 0)
	//{
	//	_cameraPos.y = WINSIZEY / 2;
	//}
	// ==========================================================
	// ###################### 장벽 구간 ##########################
	// ==========================================================
	if (_cameraRect.right > 6750)
	{
		_cameraPos.x -= _cameraRect.right - 6750;
	}
	/*if (_cameraRect.right < 7500  && _cameraRect.top < 0 )
	{
		_cameraPos.y -= _cameraRect.top;
	}*/
	// ==========================================================
	// ##########################################################
	// ==========================================================

	if (_cameraRect.right > 14070) {
		_cameraPos.x -= _cameraRect.right - 14070;
	}

	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
}

// 상대 좌표를 계산 해준다.
RECT Camera::Relative(RECT rc)
{
	rc.left -= _cameraRect.left + 300;
	rc.top -= _cameraRect.top;
	rc.right -= _cameraRect.left + 300;
	rc.bottom -= _cameraRect.top;
	return rc;
}
