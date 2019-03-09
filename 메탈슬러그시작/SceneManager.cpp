#include "stdafx.h"
#include "SceneManager.h"
#include "SceneMaker.h"

// �Ҹ��� ( ���� ����� ���� )
SceneManager::~SceneManager()
{
	// �ʿ� ����� ���� ��� �޸� ���� ���ش�.
	SceneIter = SceneList.begin();
	for (; SceneIter != SceneList.end(); ++SceneIter)
	{
		SceneIter->second->Release();
		SAFE_DELETE(SceneIter->second);
	}
	SceneList.clear();
}
// �� �ʱ�ȭ
HRESULT SceneManager::Init()
{
	CurrentScene->Init();
	return S_OK;
}
// �� ����
void SceneManager::Release()
{
	if (CurrentScene != nullptr)
		CurrentScene->Release();
}
// �� ������Ʈ
void SceneManager::Update()
{
	if ( CurrentScene != nullptr)
		CurrentScene->Update();
}
// �� ����
void SceneManager::Render()
{
	if (CurrentScene != nullptr)
		CurrentScene->Render();
}
// �� �߰� �Լ�
void SceneManager::AddScene(string name, SceneMaker * scene)
{
	SceneList.insert(make_pair(name, scene));
}
// �� �ٲٴ� �Լ�
void SceneManager::ChangeScene(string name)
{
	SceneIter = SceneList.find(name);

	if (SceneIter != SceneList.end())
	{
		if (CurrentScene != nullptr)
			CurrentScene->Release();

		CurrentScene = SceneIter->second;
		SceneIter->second->Init();
	}
}


