#pragma once
#include "GameObject.h"
class ItemUi : public GameObject
{
private:
	ITEM _item;
	bool _isShow;		//�����ٰŴ�
	bool _isVanish;		//������� �����ӷ���
	
	//�����ӷ��� ���� ����
	int _count;
	int _index;
	//���� ���� �Һ���
	bool _isTouch;		//��ҳ�?
	
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


