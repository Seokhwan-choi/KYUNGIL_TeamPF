#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// 카메라 RECT
	RECT _wallRect;					// 카메라 막기 RECT
	POINTFLOAT _cameraPos;			// 카메라 중점 좌표
	float _wall;						// 카메라 막는 범위
public:
	void SetCamera(POINTFLOAT pos);
	RECT Relative(RECT rc);
	RECT GetCamera() { return _cameraRect; }
	float GetWall() { return _wall; }

	Camera() { _wall = 0; }
	~Camera() {}
};

