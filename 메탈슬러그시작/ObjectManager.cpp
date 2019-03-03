#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
	// Ÿ���� ������ŭ map�� �����͸� �ʱ�ȭ ���ش�. 
	for (int i = 0; i <= ObjectType::UI; ++i)
	{
		// �ʿ� �����͸� ������ �� <type, vector> 2������ ���� �־�����Ѵ�.
		// pair�� make_pair�� ���� vector �����ڸ� ȣ��, �� vector(���ӿ�����Ʈ�� ����)�� ������ش�.
		// insert�� ���ؼ� �ʿ� ���� ������Ʈ�� �־��ش�.
		pair<ObjectType::Enum, vector<GameObject*>> p = make_pair((ObjectType::Enum)i,vector<GameObject*>());
		objectContainer.insert(p);
	}
}//���� insert vector�� push_back
//pair�� Ű�� �������� �ΰ��� �����ִ� 
ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{

}

void ObjectManager::Release()
{
	ObjectIter = objectContainer.begin();
	// ���� iterator�� ����ؼ� Ž���� �����Ѵ�.
	for (ObjectIter; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// ���� ObjectIter��° vector�� ����
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->second = ����
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			ObjectIter->second[i]->release();
			SAFE_DELETE(ObjectIter->second[i]);
		}
		ObjectIter->second.clear();
	}
}
// ======================================================================
// ######################### ���� ������Ʈ ������Ʈ ########################
// ======================================================================
void ObjectManager::Update()
{
	ObjectIter  = objectContainer.begin();
	// ���� iterator�� ����ؼ� Ž���� �����Ѵ�.
	for (; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// ���� iter��° vector�� ����
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->second = ����
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			// �׾��ִ� ���ӿ�����Ʈ�� ã�� Release
			if (! ObjectIter->second[i]->GetLive()) {
				ObjectIter->second[i]->release();
				SAFE_DELETE(ObjectIter->second[i]);
			}
			// Ȱ��ȭ �Ǿ��ִ� ���ӿ�����Ʈ�� ã�� Update
			if (ObjectIter->second[i]->GetActive() == true)
				ObjectIter->second[i]->Update();
		}
	}
}
// ======================================================================
// ########################## ���� ������Ʈ ���� ##########################
// ======================================================================
void ObjectManager::Render()
{	
	ObjectIter = objectContainer.begin();
	// ���� iterator�� ����ؼ� Ž���� �����Ѵ�.
	for (; ObjectIter != objectContainer.end(); ++ObjectIter)
	{
		// ���� iter��° vector�� ����
		// first-> ObjectType, second-> vector<GamObject*>
		// iter->first = ObjectType::Enum
		// iter->second = ����
		for (UINT i = 0; i < ObjectIter->second.size(); ++i)
		{
			// Ȱ��ȭ �Ǿ��ִ� ���ӿ�����Ʈ�� ã�� Render
			if (ObjectIter->second[i]->GetActive() == true)
				ObjectIter->second[i]->Render();
		}
	}
}
// ======================================================================
// ######################## ���� ������Ʈ �߰� �Լ� ########################
// ======================================================================
void ObjectManager::AddObject(ObjectType::Enum type, GameObject * pObject)
{
	// �ʿ� index�� ����ؼ� ���� ������ �����ϴ�.
	// index = ObjectType::Enum 
	// �ش� �ε����� ���Ϳ� �����Ͽ� push_back 

	// �������� ���� �Ῡ�� ������� ���� �ʴ�. Why?
	// �ش� �����Ϸ��� type�� �ƹ��͵� ���� ����������
	// ���ʿ��� �޸� ������ ���� �Ҵ��Ѵ�.
	// this->objectContainer[type].push_back(pObject);

	// ************* �������� �ִ� ��� *************
	// ���� ã�����ϴ� type�� �ʿ� �����ϴ��� Ȯ���Ѵ�.
	// find�� ����ϸ� ã�����ϴ� Ÿ���� �ݺ��ڸ� ����ش�.
	ObjectIter = objectContainer.find(type);
	// �ݺ��ڸ� ���ؼ� ���� ���� ���� �ƴ϶��
	// type�� �ʿ��� ã�Ҵٴ� ������
	// �� �� vector�� �־��ش�.
	if (ObjectIter != objectContainer.end()) //end��� ���� null�� ���ٴ� ���̴� 
	{
		objectContainer[type].push_back(pObject);
	}
}//�ʿ��� find�� �Ἥ �ش� Ÿ���� ������ 
// ======================================================================
// ######################## ���� ������Ʈ ���� �Լ� ########################
// ======================================================================
void ObjectManager::RemoveObject(ObjectType::Enum type, GameObject * pObject)
{
	// �����ϰ����ϴ� type�� �ʿ��� ã�´�.
	ObjectIter = objectContainer.find(type);
	
	//if ( ObjectIter != objectContainer.end()))
	// �ش� type�� vector�� Ž���Ѵ�.
	for (UINT i = 0; i < ObjectIter->second.size(); ++i)
	{
		// vector�� ����ִ� �ش� ���ӿ�����Ʈ�� ã����
		if (ObjectIter->second[i] == pObject)
		{
			// �޸𸮸� �������ְ�
			// ���Ϳ��� �������ش�.
			ObjectIter->second[i]->Release();
			SAFE_DELETE(ObjectIter->second[i]);
			ObjectIter->second.erase(ObjectIter->second.begin() + i);
			break;
		}
	}
}
// ======================================================================
// ######################## ���� ������Ʈ ã�� �Լ� ########################
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

	return nullptr;//�̰� ���� 
}
// ======================================================================
// #################### ���� �̸� ���� ������Ʈ ã�� �Լ� ####################
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
	}//��� 10��������� �Ѳ����� �������� 
	return returnValue;
}
// ======================================================================
// ###################### ���� ������Ʈ ��ü ��ȯ �Լ� ######################
// ======================================================================
vector<class GameObject*> ObjectManager::GetObjectList(ObjectType::Enum type)
{
	return objectContainer[type];
}
