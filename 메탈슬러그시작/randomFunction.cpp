#include "stdafx.h"
#include "randomFunction.h"


HRESULT randomFunction::init(void)
{
	//�����õ� �ʱ�ȭ
	srand(GetTickCount());
	return S_OK;
}

void randomFunction::release(void)
{
}


// 0 ~ (num-1)������ ������
int randomFunction::range(int num)
{
	return rand() % num;
}


//fromNum ~ toNum ������ ������
int randomFunction::range(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}