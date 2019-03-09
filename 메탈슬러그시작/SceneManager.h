#pragma once
#include "SingletonBase.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, class SceneMaker*> SceneList;				// ¾À ¸®½ºÆ®
	map<string, class SceneMaker*>::iterator SceneIter;		// ¾À ¹İº¹ÀÚ
	class SceneMaker* CurrentScene;							// ÇöÀç ¾À
public:

	HRESULT Init();			// ¾À ÃÊ±âÈ­
	void Release();			// ¾À ÇØÁ¦
	void Update();			// ¾À ¾÷µ¥ÀÌÆ®
	void Render();			// ¾À ·»´õ

	void AddScene(string name, class SceneMaker* scene); // ¾À Ãß°¡
	void ChangeScene(string name);						 // ¾À ¹Ù²ãÁÖ±â

	// »ı¼ºÀÚ ÇöÀç ¾À nullptr ÃÊ±âÈ­
	SceneManager() { CurrentScene = nullptr; }
	// ¼Ò¸êÀÚ
	~SceneManager();	
};

#define SCENEMANAGER SceneManager::getSingleton()

