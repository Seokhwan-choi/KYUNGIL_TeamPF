#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
	// 타입의 갯수만큼 map에 데이터를 초기화 해준다. 
	for (int i = 0; i <= ObjectType::UI; ++i)
	{
		// 맵에 데이터를 삽입할 때 <type, vector> 2가지를 같이 넣어줘야한다.
		// pair를 make_pair를 통해 vector 생성자를 호출, 빈 vector(게임오브젝트를 담을)를 만들어준다.
		// insert를 통해서 맵에 게임 오브젝트를 넣어준다.
		pair<ObjectType::Enum, vector<GameObject*>> p = make_pair((ObjectType::Enum)i,vector<GameObject*>());
		objectContainer.insert(p);
	}
}//맵은 insert vector는 push_back
//pair는 키값 벨류값을 두개다 갖고있다 
ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{

}

void ObjectManager::Release()
{
	ObjectIter = objectContainer.begin();
	// 맵을 iterator를 사용해서 탐색을 시작한다.
	for (ObjectIter; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// 맵의 ObjectIter번째 vector에 접근
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->second = 벡터
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			ObjectIter->second[i]->release();
			SAFE_DELETE(ObjectIter->second[i]);
		}
		ObjectIter->second.clear();
	}
}
// ======================================================================
// ######################### 게임 오브젝트 업데이트 ########################
// ======================================================================
void ObjectManager::Update()
{
	ObjectIter  = objectContainer.begin();
	// 맵을 iterator를 사용해서 탐색을 시작한다.
	for (; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// 맵의 iter번째 vector에 접근
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->second = 벡터
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			// 죽어있는 게임오브젝트를 찾아 Release
			if (! ObjectIter->second[i]->GetLive()) {
				ObjectIter->second[i]->release();
				SAFE_DELETE(ObjectIter->second[i]);
			}
			// 활성화 되어있는 게임오브젝트를 찾아 Update
			if (ObjectIter->second[i]->GetActive() == true)
				ObjectIter->second[i]->Update();
		}
	}
}
// ======================================================================
// ########################## 게임 오브젝트 랜더 ##########################
// ======================================================================
void ObjectManager::Render()
{	
	ObjectIter = objectContainer.begin();
	// 맵을 iterator를 사용해서 탐색을 시작한다.
	for (; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// 맵의 iter번째 vector에 접근
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->first = ObjectType::Enum
		// iter->second = 벡터
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			// 활성화 되어있는 게임오브젝트를 찾아 Render
			if (ObjectIter->second[i]->GetActive() == true)
				ObjectIter->second[i]->Render();
		}
	}
}
// ======================================================================
// ######################## 게임 오브젝트 추가 함수 ########################
// ======================================================================
void ObjectManager::AddObject(ObjectType::Enum type, GameObject * pObject)
{
	// 맵에 index를 사용해서 직접 접근이 가능하다.
	// index = ObjectType::Enum 
	// 해당 인덱스의 벡터에 접근하여 push_back 

	// 안정성이 많이 결여된 방법으로 좋지 않다. Why?
	// 해당 접근하려는 type에 아무것도 존재 하지않으면
	// 불필요한 메모리 공간을 새로 할당한다.
	// this->objectContainer[type].push_back(pObject);

	// ************* 안정성이 있는 방법 *************
	// 먼저 찾고자하는 type이 맵에 존재하는지 확인한다.
	// find를 사용하면 찾고자하는 타입의 반복자를 뱉어준다.
	ObjectIter = objectContainer.find(type);
	// 반복자를 통해서 맵의 가장 끝이 아니라면
	// type을 맵에서 찾았다는 뜻으로
	// 그 때 vector에 넣어준다.
	if (ObjectIter != objectContainer.end()) //end라는 말은 null값 없다는 뜻이다 
	{
		objectContainer[type].push_back(pObject);
	}
}//맵에서 find를 써서 해당 타입을 적으면 
// ======================================================================
// ######################## 게임 오브젝트 삭제 함수 ########################
// ======================================================================
void ObjectManager::RemoveObject(ObjectType::Enum type, GameObject * pObject)
{
	// 접근하고자하는 type을 맵에서 찾는다.
	ObjectIter = objectContainer.find(type);
	
	//if ( ObjectIter != objectContainer.end()))
	// 해당 type의 vector를 탐색한다.
	for (UINT i = 0; i < ObjectIter->second.size(); ++i)
	{
		// vector에 들어있는 해당 게임오브젝트를 찾으면
		if (ObjectIter->second[i] == pObject)
		{
			// 메모리를 해제해주고
			// 벡터에서 삭제해준다.
			ObjectIter->second[i]->Release();
			SAFE_DELETE(ObjectIter->second[i]);
			ObjectIter->second.erase(ObjectIter->second.begin() + i);
			break;
		}
	}
}
// ======================================================================
// ######################## 게임 오브젝트 찾기 함수 ########################
// ======================================================================
GameObject * ObjectManager::FindObject(ObjectType::Enum type, string name)
{
	for (UINT i = 0; i < objectContainer[type].size(); ++i)
	{
		if (objectContainer[type][i]->GetName() == name)
		{
			return objectContainer[type][i];
		}
	}

	return nullptr;//이건 걍널 
}
// ======================================================================
// #################### 같은 이름 게임 오브젝트 찾기 함수 ####################
// ======================================================================
vector<class GameObject*> ObjectManager::FindObjects(ObjectType::Enum type, string name)
{
	vector<GameObject*> returnValue;
	for (UINT i = 0; i < objectContainer[type].size(); ++i)
	{
		if (objectContainer[type][i]->GetName() == name)
		{
			returnValue.push_back(objectContainer[type][i]);
		}
	}//고블린 10마리만들고 한꺼번에 뱉을려고 
	return returnValue;
}
// ======================================================================
// ###################### 게임 오브젝트 전체 반환 함수 ######################
// ======================================================================
vector<class GameObject*> ObjectManager::GetObjectList(ObjectType::Enum type)
{
	return objectContainer[type];
}
