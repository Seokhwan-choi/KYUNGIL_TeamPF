#pragma once
#include "GameObject.h"
class Fish : public GameObject
{
private:
	//상태
	STATE _state;
	//플레이어
	class Player* player;
	//물고기 렉트
	RECT Fish_Rc;
	//카메라 구조체
	CAM _cam;
	//물고기 패턴을 위한 카운트
	int count;

public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

