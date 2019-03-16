#pragma once
#include "SingletonBase.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, class SceneMaker*> SceneList;				// �� ����Ʈ
	map<string, class SceneMaker*>::iterator SceneIter;		// �� �ݺ���
	SceneMaker* CurrentScene;								// ���� ��
public:

	HRESULT Init();			// �� �ʱ�ȭ
	void Release();			// �� ����
	void Update();			// �� ������Ʈ
	void Render();			// �� ����

	bool FindScene(string name);
	void AddScene(string name, class SceneMaker* scene); // �� �߰�
	void ChangeScene(string name);						 // �� �ٲ��ֱ�
	SceneMaker* GetScene(string name);

														 // ������ ���� �� nullptr �ʱ�ȭ
	SceneManager() { CurrentScene = nullptr; }
	// �Ҹ���
	~SceneManager();
};



