#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// ī�޶� RECT
	RECT _wallRect;					// ī�޶� ���� RECT
	POINTFLOAT _cameraPos;			// ī�޶� ���� ��ǥ
	int _wall;                      // �츮�� �ڷθ� ���������ϴ� ��??
public:

	void SetCamera(POINTFLOAT pos, bool check);           //ī�޶��� ����  
	void SetCamera2(POINTFLOAT pos);
	void SetCamera3(POINTFLOAT pos);
	RECT Relative(RECT rc);                   //ī�޶��� �����ǥ�� ������ִ³༮ 
	RECT GetCamera() { return _cameraRect; }  //ī�޶� RECT�� ��ȯ�ϴ��Լ�   ��濡�� ���ٷ��� ���뾴�� 
	                                          //���� ����ҋ� 
	RECT GetRelativeCamera(RECT rc);

	void SetWall(int w) { _wall = w; }         //WALL�� 0??�ǿ����̴�??
	int GetWall() { return _wall; }


	Camera()
	{ 
		_wall = 0; //�����ڰ� Ŭ������ ȣ��ɋ� ���ѹ� ȣ��Ǽ� 
		         //���̹ٲ�� �̱����� �׻� ������ �ٽ� �ʱ�ȭ�ؾ��Ѵ� 
	}
	~Camera() {}
};

//
//// ī�޶� ��ġ�� ���� ���ش�.
//void Camera::SetCamera(POINTFLOAT pos)
//{
//	// �ش� Ÿ���� �߽����� ī�޶� �׷��ش�.
//	_cameraPos = pos;
//	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
//
//	if (_cameraRect.left >= wall)
//	{
//		wall = _cameraRect.left;  //���Ⱑ left���� ���� ���� 
//	}
//
//
//	if (_cameraRect.left < wall)
//	{
//		_cameraPos.x = _cameraPos.x + (wall - _cameraRect.left);
//	}
//
//	if (_cameraRect.bottom > 958)
//	{
//		_cameraPos.y -= (_cameraRect.bottom - 958);
//	}
//
//	// �߰� ����
//	// �߰������� ī�޶��� ��ġ�� ��������� �Ѵ�.
//	if (_cameraRect.top <= 0)
//	{
//		_cameraPos.y = _cameraPos.y + (0 - _cameraRect.top);
//	}
//
//	// ==========================================================
//	// ###################### �庮 ���� ##########################
//	// ==========================================================
//	//if (_cameraRect.right > 6750)
//	//{
//	//	_cameraPos.x -= _cameraRect.right - 6750;
//	//}
//	//else {
//	//	
//	//}
//	//
//	//if (_cameraRect.right < 7500
//	//	&& _cameraRect.top < 0 ) {
//	//	_cameraPos.y -= _cameraRect.top;
//	//}
//	// ==========================================================
//	// ##########################################################
//	// ==========================================================
//
//	if (_cameraRect.right > 14070) {
//		_cameraPos.x -= _cameraRect.right - 14070;
//	}
//
//	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
//}
