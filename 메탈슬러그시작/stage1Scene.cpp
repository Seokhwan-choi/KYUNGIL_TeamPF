#include "stdafx.h"
#include "stage1Scene.h"

HRESULT stage1Scene::Init(void)
{
	return S_OK;
}

void stage1Scene::Release(void)
{
	OBJECTMANAGER->Release();
}

void stage1Scene::Update(void)
{
	OBJECTMANAGER->Update();
}

void stage1Scene::Render(void)
{
	OBJECTMANAGER->Render();
}
