#pragma once
#include "GameObject.h"
class BigCrab : public GameObject
{
private:
	//상태
	STATE _state;
	//카메라 구조체
	CAM _cam[3];
	//충돌 구조체
	COL _col[4];
	//플레이어 클래스
	class Player* player;
public:
	BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BigCrab();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Attcol();
	void rectmove();
};

