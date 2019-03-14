#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

// 카메라 위치를 세팅 해준다.
void Camera::SetCamera(POINTFLOAT pos)
{
	// 해당 타겟을 중심으로 카메라를 그려준다.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);

	if (_cameraRect.left >= wall)
	{
		wall = _cameraRect.left;  //여기가 left보다 나간 차이 
	}


	if (_cameraRect.left < wall)
	{
		_cameraPos.x = _cameraPos.x + (wall - _cameraRect.left);
	}

	//wall = wall - _cameraRect.left; 

	//a = _cameraPos.x - _cameraRect.left;

	/*if (_cameraRect.left < 0)
	{
		_cameraPos.x -= _cameraRect.left;
	}*/


	 if (_cameraRect.bottom > 958)
	{
		_cameraPos.y -= (_cameraRect.bottom - 958);
	}

	 // 추가 예정
	// 추가적으로 카메라의 위치를 보정해줘야 한다.
	 if (_cameraRect.top <= 0)
	 {
		 _cameraPos.y = _cameraPos.y +(0- _cameraRect.top);
	 }

	// ==========================================================
	// ###################### 장벽 구간 ##########################
	// ==========================================================
	//if (_cameraRect.right > 6750)
	//{
	//	_cameraPos.x -= _cameraRect.right - 6750;
	//}
	//else {
	//	
	//}
	//
	//if (_cameraRect.right < 7500
	//	&& _cameraRect.top < 0 ) {
	//	_cameraPos.y -= _cameraRect.top;
	//}
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
