#pragma once
#include "GameObject.h"
class BigCrab : public GameObject
{
private:
	//����
	STATE _state;
	//ī�޶� ����ü
	CAM _cam[3];
	//�浹 ����ü
	COL _col[4];
	//�÷��̾� Ŭ����
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

