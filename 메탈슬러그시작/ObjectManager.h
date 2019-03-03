#pragma once
#include "SingletonBase.h"

//이름표 
namespace ObjectType
{
	// 게임 오브젝트 type 
	enum Enum : int
	{
		MAP, ENEMY, BOSS, PLAYER, ITEM, UI, END
	};
}

class ObjectManager : public SingletonBase<ObjectManager>
{
private:
	// 맵 반복자, typedef 사용하여 ObjectIter를 선언하여 반복자 사용가능
	//typedef map<ObjectType::Enum, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectType::Enum, vector<class GameObject*>>::iterator ObjectIter;
private:
	// 맵을 통해서 게임 오브젝트를 관리, <게임오브젝트 타입, 게임오브젝트를 담은 벡터>
	map<ObjectType::Enum, vector<class GameObject*>> objectContainer;
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render();
public:
	void AddObject(ObjectType::Enum type, class GameObject* pObject);			// 게임 오브젝트 추가
	void RemoveObject(ObjectType::Enum type, class GameObject* pObject);		// 게임 오브젝트 삭제
	class GameObject* FindObject(ObjectType::Enum type, string name);			// 게임 오브젝트 찾기
	vector<class GameObject*> FindObjects(ObjectType::Enum type, string name);	// 게임 오브젝트 찾기(같은 이름 모두) ex) "몬스터" 여러마리, "총알" 여러개
	vector<class GameObject*> GetObjectList(ObjectType::Enum type);				// 해당 타입 게임 오브젝트 벡터 반환 


};

// 싱글톤 사용을 위해서 define 정의
#define OBJECTMANAGER ObjectManager::getSingleton()
