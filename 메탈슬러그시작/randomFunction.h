#pragma once
#include "SingletonBase.h"
class randomFunction :	public SingletonBase<randomFunction>
{
private:

public:
	HRESULT init(void);
	void release(void);

	//GetInt
	int range(int num);
	//GetFromIntTo
	int range(int fromNum, int toNum);

	randomFunction() {}
	~randomFunction() {}
};

