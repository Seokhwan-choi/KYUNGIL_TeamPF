#pragma once
#include "SingletonBase.h"

//�̸�ǥ 
namespace ObjectType
{
	// ���� ������Ʈ type 
	enum Enum : int
	{
		MAP, ENEMY, BOSS, PLAYER, ITEM, UI, END
	};
}

class ObjectManager : public SingletonBase<ObjectManager>
{
private:
	// �� �ݺ���, typedef ����Ͽ� ObjectIter�� �����Ͽ� �ݺ��� ��밡��
	//typedef map<ObjectType::Enum, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectType::Enum, vector<class GameObject*>>::iterator ObjectIter;
private:
	// ���� ���ؼ� ���� ������Ʈ�� ����, <���ӿ�����Ʈ Ÿ��, ���ӿ�����Ʈ�� ���� ����>
	map<ObjectType::Enum, vector<class GameObject*>> objectContainer;
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render();
public:
	void AddObject(ObjectType::Enum type, class GameObject* pObject);			// ���� ������Ʈ �߰�
	void RemoveObject(ObjectType::Enum type, class GameObject* pObject);		// ���� ������Ʈ ����
	class GameObject* FindObject(ObjectType::Enum type, string name);			// ���� ������Ʈ ã��
	vector<class GameObject*> FindObjects(ObjectType::Enum type, string name);	// ���� ������Ʈ ã��(���� �̸� ���) ex) "����" ��������, "�Ѿ�" ������
	vector<class GameObject*> GetObjectList(ObjectType::Enum type);				// �ش� Ÿ�� ���� ������Ʈ ���� ��ȯ 


};

// �̱��� ����� ���ؼ� define ����
#define OBJECTMANAGER ObjectManager::getSingleton()
