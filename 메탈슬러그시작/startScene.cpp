#include "stdafx.h"
#include "startScene.h"
#include "startUi.h"
HRESULT startScene::Init(void)
{

	//시작화면을 중심점에 잡아주고 전체 화면으로 맞춰준다.
	startUi* _startui = new startUi("startui", { WINSIZEX / 2, WINSIZEY / 2 }, { WINSIZEX, WINSIZEY }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::UI, _startui);

	return S_OK;
}

void startScene::Release(void)
{
	OBJECTMANAGER->Release();
}

void startScene::Update(void)
{
	OBJECTMANAGER->Update();
}

void startScene::Render(void)
{
	OBJECTMANAGER->Render();
}
