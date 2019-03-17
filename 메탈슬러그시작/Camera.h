#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	RECT _cameraRect;				// 카메라 RECT
	RECT _wallRect;					// 카메라 막기 RECT
	POINTFLOAT _cameraPos;			// 카메라 중점 좌표
	int _wall;                      // 우리가 뒤로못 지나가게하는 벽??
public:

	void SetCamera(POINTFLOAT pos, bool check);           //카메라의 중점  
	void SetCamera2(POINTFLOAT pos);
	void SetCamera3(POINTFLOAT pos);
	RECT Relative(RECT rc);                   //카메라의 상대좌표를 계산해주는녀석 
	RECT GetCamera() { return _cameraRect; }  //카메라 RECT를 반환하는함수   배경에서 빼줄려고 보통쓴다 
	                                          //보통 배경할떄 
	RECT GetRelativeCamera(RECT rc);

	void SetWall(int w) { _wall = w; }         //WALL은 0??맨왼쪽이다??
	int GetWall() { return _wall; }


	Camera()
	{ 
		_wall = 0; //생성자가 클래스가 호출될떄 딱한번 호출되서 
		         //씬이바뀌면 싱글톤은 항상 쓸꺼는 다시 초기화해야한다 
	}
	~Camera() {}
};

//
//// 카메라 위치를 세팅 해준다.
//void Camera::SetCamera(POINTFLOAT pos)
//{
//	// 해당 타겟을 중심으로 카메라를 그려준다.
//	_cameraPos = pos;
//	_cameraRect = RectMakeCenter(_cameraPos.x, _cameraPos.y, WINSIZEX, WINSIZEY);
//
//	if (_cameraRect.left >= wall)
//	{
//		wall = _cameraRect.left;  //여기가 left보다 나간 차이 
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
//	// 추가 예정
//	// 추가적으로 카메라의 위치를 보정해줘야 한다.
//	if (_cameraRect.top <= 0)
//	{
//		_cameraPos.y = _cameraPos.y + (0 - _cameraRect.top);
//	}
//
//	// ==========================================================
//	// ###################### 장벽 구간 ##########################
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
