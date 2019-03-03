#pragma once

template<class T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//�̱��� ��������.
	static T* getSingleton(void);

	//�̱��� �޸𸮿��� �����ϱ�.
	void releaseSingleton(void);
};

//�̱��� �ʱ�ȭ
template <class T>
T* SingletonBase<T>::singleton = 0;

//�̱��� ��������.
template<class T>
inline T * SingletonBase<T>::getSingleton(void)
{
	//�̱����� ������ ���� ��������.
	if (!singleton) 
		singleton = new T;
	return singleton;
}

//�̱��� �޸𸮿��� �����ϱ�.
template<class T>
inline void SingletonBase<T>::releaseSingleton(void)
{
	//�̱����� �ִٸ� �޸𸮿��� ����
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
