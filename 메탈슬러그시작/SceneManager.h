#pragma once
#include "SingletonBase.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, class SceneMaker*> SceneList;				// �� ����Ʈ
	map<string, class SceneMaker*>::iterator SceneIter;		// �� �ݺ���
	class SceneMaker* CurrentScene;							// ���� ��
public:

	HRESULT Init();			// �� �ʱ�ȭ
	void Release();			// �� ����
	void Update();			// �� ������Ʈ
	void Render();			// �� ����

	void AddScene(string name, class SceneMaker* scene); // �� �߰�
	void ChangeScene(string name);						 // �� �ٲ��ֱ�

	// ������ ���� �� nullptr �ʱ�ȭ
	SceneManager() { CurrentScene = nullptr; }
	// �Ҹ���
	~SceneManager();	
};

#define SCENEMANAGER SceneManager::getSingleton()

