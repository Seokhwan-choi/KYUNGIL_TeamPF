#include "stdafx.h"
#include "Camera.h"

// ī�޶� ��ġ�� ���� ���ش�.
void Camera::SetCamera(POINTFLOAT pos)
{
	// �ش� Ÿ���� �߽����� ī�޶� �׷��ش�.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);

	// �߰� ����
	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.

	if (_cameraRect.left < 0) 
	{
		_cameraPos.x -= _cameraRect.left;
	}

	// ==========================================================
	// ###################### �庮 ���� ##########################
	// ==========================================================
	if (_cameraRect.right > 6750)
	{
		_cameraPos.x -= _cameraRect.right - 6750;
	}
	if (_cameraRect.right < 7500
		&& _cameraRect.top < 0 ) {
		_cameraPos.y -= _cameraRect.top;
	}
	// ==========================================================
	// ##########################################################
	// ==========================================================

	if (_cameraRect.right > 14070) {
		_cameraPos.x -= _cameraRect.right - 14070;
	}

	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
}

// ��� ��ǥ�� ��� ���ش�.
RECT Camera::Relative(RECT rc)
{
	rc.left -= _cameraRect.left + 300;
	rc.top -= _cameraRect.top;
	rc.right -= _cameraRect.left + 300;
	rc.bottom -= _cameraRect.top;
	return rc;
}
