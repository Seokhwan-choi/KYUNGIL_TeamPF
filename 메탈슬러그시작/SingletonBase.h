#pragma once

template<class T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//싱글톤 가져오기.
	static T* getSingleton(void);

	//싱글톤 메모리에서 해제하기.
	void releaseSingleton(void);
};

//싱글톤 초기화
template <class T>
T* SingletonBase<T>::singleton = 0;

//싱글톤 가져오기.
template<class T>
inline T * SingletonBase<T>::getSingleton(void)
{
	//싱글톤이 없으면 새로 생성하자.
	if (!singleton) 
		singleton = new T;
	return singleton;
}

//싱글톤 메모리에서 해제하기.
template<class T>
inline void SingletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면 메모리에서 해제
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
