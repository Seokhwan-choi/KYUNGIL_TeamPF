#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

// ī�޶� ��ġ�� ���� ���ش�.
void Camera::SetCamera(POINTFLOAT pos, bool check)
{
	// �ش� Ÿ���� �߽����� ī�޶� �׷��ش�.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);

	// �߰� ����
	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.

	if (_cameraRect.left < _wall)// && _cameraRect.left > 0) 
	{
		_cameraPos.x += _wall - _cameraRect.left;
	}

	 if (_cameraRect.bottom > 958)
	{
		_cameraPos.y -= (_cameraRect.bottom - 958);
	}

	 // �߰� ����
	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.
	 if (_cameraRect.top <= 0)
	 {
		 _cameraPos.y = _cameraPos.y +(0- _cameraRect.top);
	 }

	// ==========================================================
	// ###################### �庮 ���� ##########################
	// ==========================================================
	if (_cameraRect.right > 6750 && !check)
	{
		_cameraPos.x -= _cameraRect.right - 6750;
	}
	else {
		if (_cameraRect.left >= _wall)
		{
			_wall = _cameraRect.left;
		}
	}
	// ==========================================================
	// ##########################################################
	// ==========================================================

	if (_cameraRect.right > 14070) {
		_cameraPos.x -= _cameraRect.right - 14070;
	}

	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
}

void Camera::SetCamera2(POINTFLOAT pos)
{
	_cameraPos = pos; 
	_cameraRect = RectMakeCenter(_cameraPos.x,_cameraPos.y,WINSIZEX,WINSIZEY);

	

	if (_cameraRect.left < _wall)
	{
		_cameraPos.x = _cameraPos.x + (_wall - _cameraRect.left);
	}
	// 6774 x 958 

	if (_cameraRect.bottom > 958)
	{
		_cameraPos.y -= (_cameraRect.bottom - 958); 
	}
	if (_cameraRect.top <= 0)
	{
		_cameraPos.y = _cameraPos.y + (0 - _cameraRect.top);
	}

	if (_cameraRect.right > 6474)
	{                    //6700              //7000     
		_cameraPos.x -= (_cameraRect.right - 6474);   
	}
	else 
	{
		if (_cameraRect.left >= _wall)
		{
			_wall = _cameraRect.left;
		}
	}

	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY); 

}

void Camera::SetCamera3(POINTFLOAT pos)
{

	// �ش� Ÿ���� �߽����� ī�޶� �׷��ش�.
	_cameraPos = pos;
	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);

	if (_cameraRect.bottom > WINSIZEY)
	{
		_cameraPos.y -= (_cameraRect.bottom - WINSIZEY);
	}

	// �߰� ����
	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.
	if (_cameraRect.top <= 0)
	{
		_cameraPos.y = _cameraPos.y + (0 - _cameraRect.top);
	}

	if (_cameraRect.right > WINSIZEX) {
		_cameraPos.x -= _cameraRect.right - WINSIZEX;
	}

	if (_cameraRect.left < 0) {
		_cameraPos.x -= _cameraRect.left;
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

