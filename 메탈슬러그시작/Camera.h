#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// ī�޶� RECT
	RECT _wallRect;					// ī�޶� ���� RECT
	POINTFLOAT _cameraPos;			// ī�޶� ���� ��ǥ
	float _wall;						// ī�޶� ���� ����
public:
	void SetCamera(POINTFLOAT pos);
	RECT Relative(RECT rc);
	RECT GetCamera() { return _cameraRect; }
	float GetWall() { return _wall; }

	Camera() { _wall = 0; }
	~Camera() {}
};

