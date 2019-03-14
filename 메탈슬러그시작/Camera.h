#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// ī�޶� RECT
	POINTFLOAT _cameraPos;			// ī�޶� ���� ��ǥ
	int wall;
public:

	void SetCamera(POINTFLOAT pos);
	RECT Relative(RECT rc);
	RECT GetCamera() { return _cameraRect; }

	int GetWall() { return wall; }


	Camera()
	{ 
		wall = 0;
	}
	~Camera() {}
};

