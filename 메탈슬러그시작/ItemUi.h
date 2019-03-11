#pragma once
#include "GameObject.h"
class ItemUi : public GameObject
{
private:
	ITEM _item;
	bool _isShow;
	bool _isVanish;

public:
	ItemUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~ItemUi();
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

};


