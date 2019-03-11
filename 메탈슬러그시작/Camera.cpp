#include "stdafx.h"
#include "Camera.h"

// ī�޶� ��ġ�� ���� ���ش�.
void Camera::SetCamera(POINTFLOAT pos)
{
	// �ش� Ÿ���� �߽����� ī�޶� �׷��ش�.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);


	//if (_cameraPos.x - WINSIZEX / 2 < 0)
	//{
	//	_cameraPos.x = WINSIZEX / 2;
	//}

	// �߰� ����
	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.

	if (_cameraRect.left < 0)                   //���� �ȹ���� 
	{
		_cameraPos.x = _cameraPos.x - _cameraRect.left;//�̷��� �������ִ�  �������Ǽ� --�Ǹ�+���Ǵٴµ�?
		//_cameraPos.x = WINSIZEX / 2;       //���̰����� ��
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
	// ###################### �庮 ���� ##########################
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

// ��� ��ǥ�� ��� ���ش�.
RECT Camera::Relative(RECT rc)
{
	rc.left -= _cameraRect.left + 300;
	rc.top -= _cameraRect.top;
	rc.right -= _cameraRect.left + 300;
	rc.bottom -= _cameraRect.top;
	return rc;
}
