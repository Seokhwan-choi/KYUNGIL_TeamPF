#include "stdafx.h"
#include "randomFunction.h"


HRESULT randomFunction::init(void)
{
	//랜덤시드 초기화
	srand(GetTickCount());
	return S_OK;
}

void randomFunction::release(void)
{
}


// 0 ~ (num-1)사이의 랜덤값
int randomFunction::range(int num)
{
	return rand() % num;
}


//fromNum ~ toNum 사이의 랜덤값
int randomFunction::range(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}