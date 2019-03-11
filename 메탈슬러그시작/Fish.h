#pragma once
#include "GameObject.h"

typedef struct fish
{
	//물고기 렉트
	RECT Fish_Rc;
	//불변수
	bool isFish;
	//카운트 변수
	int count;
	//이미지 랜더용 변수
	int Imgcount[3];
	int Imgindex[3];
	//이미지용 불변수
	bool Imgchange;
	//물고기 데스카운트
	int fish_death;
}Fish_t;

class Fish : public GameObject
{
private:
	//상태
	STATE _state;
	//플레이어
	class Player* player;
	//카메라 구조체
	CAM _cam;
	//물고기 패턴을 위한 카운트
	int count;
	//물고기 구조체
	Fish_t fish_rc[8];
	//물고기 이미지
	image* fishImg[3];
	//카운터
	int count_death;
	

public:
	Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Fish();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

