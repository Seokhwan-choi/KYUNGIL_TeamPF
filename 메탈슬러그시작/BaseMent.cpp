#include "stdafx.h"
#include "BaseMent.h"





HRESULT BaseMent::Init(void)
{
	bgImage = IMAGEMANAGER->addImage("���Ϲ��", "���Ϲ��.bmp", 5000, 5000);

	return S_OK;
}

void BaseMent::Release(void)
{
}

void BaseMent::Update(void)
{

}

void BaseMent::Render(void)
{
	bgImage->render(getMemDC());
}
