#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// 카메라 RECT
	POINTFLOAT _cameraPos;			// 카메라 중점 좌표
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

