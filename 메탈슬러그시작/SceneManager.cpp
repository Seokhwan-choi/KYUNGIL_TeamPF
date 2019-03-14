#include "stdafx.h"
#include "SceneManager.h"
#include "SceneMaker.h"

// ¼Ò¸êÀÚ ( °ÔÀÓ Á¾·á½Ã µ¿ÀÛ )
SceneManager::~SceneManager()
{
	// ¸Ê¿¡ ÀúÀåµÈ ¾Àµé ¸ðµÎ ¸Þ¸ð¸® ÇØÁ¦ ÇØÁØ´Ù.
	SceneIter = SceneList.begin();
	for (; SceneIter != SceneList.end(); ++SceneIter)
	{
		SceneIter->second->Release();
		SAFE_DELETE(SceneIter->second);
	}
	SceneList.clear();
}
// ¾À ÃÊ±âÈ­
HRESULT SceneManager::Init()
{
	CurrentScene->Init();
	return S_OK;
}
// ¾À ÇØÁ¦
void SceneManager::Release()
{
	if (CurrentScene != nullptr)
		CurrentScene->Release();
}
// ¾À ¾÷µ¥ÀÌÆ®
void SceneManager::Update()
{
	if (CurrentScene != nullptr)
		CurrentScene->Update();
}
// ¾À ·»´õ
void SceneManager::Render()
{
	if (CurrentScene != nullptr)
		CurrentScene->Render();
}
// ¾À Ãß°¡ ÇÔ¼ö
void SceneManager::AddScene(string name, SceneMaker * scene)
{
	SceneList.insert(make_pair(name, scene));
}
// ¾À ¹Ù²Ù´Â ÇÔ¼ö
void SceneManager::ChangeScene(string name)
{
	SceneIter = SceneList.find(name);

	if (SceneIter != SceneList.end())
	{
		if (CurrentScene != nullptr)
			CurrentScene->Release();

		CurrentScene = SceneIter->second;
		CurrentScene->Init();
	}
}