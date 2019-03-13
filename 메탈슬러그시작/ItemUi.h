#pragma once
#include "GameObject.h"
class ItemUi : public GameObject
{
private:
	ITEM _item;
	bool _isShow;		//보여줄거다
	bool _isVanish;		//사라질때 프레임랜더
	
	//프레임랜더 관련 변수
	int _count;
	int _index;
	//점수 관련 불변수
	bool _isTouch;		//닿았냐?
	
public:
	ItemUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, ITEM item);
	~ItemUi();
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);
	
	void setShow(bool isshow) { _isShow = isshow; }
	bool getShow() { return _isShow; }

	void setVanish(bool isvanish) { _isVanish = isvanish; }
	bool getVanish() { return _isVanish; }

	enum ITEM getItem() { return _item; }
	void setItem(enum ITEM item) { _item = item; }
	

};


