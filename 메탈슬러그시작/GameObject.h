#pragma once
#include "gameNode.h"
class GameObject : public gameNode
{
public: 
	// enum class �� pivot ���� ���
	// pivot�� ���� RECT ���� �������� ����
	enum class Pivot : int
	{
		LeftTop,		// RectMake
		Center,			// RectMakeCeter
		Bottom			// RectMakeBottom
	};

protected:
	// protected�� �������
	// ��Ӱ��迡���� ��밡��
	string _name;					// ���ӿ�����Ʈ �̸�
	Pivot _pivot;					// ���ӿ�����Ʈ �ǹ�(RECT�� �׸��� ������)
	POINTFLOAT _position;			// ���ӿ�����Ʈ ��ǥ
	POINTFLOAT _size;				// ���ӿ�����Ʈ ũ��
	RECT _rc;						// ���ӿ�����Ʈ RECT
	bool _isActive;					// ���ӿ�����Ʈ Ȱ��ȭ���ֳ�?
	bool _isLive;					// ���ӿ�����Ʈ ����ֳ�?
public:
	// ���ӿ�����Ʈ �����ڸ� ���ؼ� ������� �ʱ�ȭ ���ش�.
	GameObject(string name,POINTFLOAT pos,POINTFLOAT size,Pivot pivot);
	GameObject(string name);
	~GameObject();

	// virtual�� �ٿ��־� �ڽĵ��� override(������) �ؼ� ��� �� �� �ְ�
	// gameNode�� �����Ƶ� virtual �����ִ�.
	// ���ӿ�����Ʈ ��ӹ��� Ŭ������ override �����ְ� ���
	// ex) void Init() override;
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(); 


	// �� ��������� ���� get�� ������ش�.
	string GetName()const { return this->_name; }
	POINTFLOAT GetPosition()const { return this->_position; }
	POINTFLOAT GetSize()const { return this->_size; }
	RECT GetRect()const { return this->_rc; }
	bool GetActive()const { return this->_isActive; }
	bool GetLive()const { return this->_isLive; }
	// �� ��������� ���� set�� ������ش�.
	void SetName(string name) { _name = name; }
	void SetisActive(bool isActive) { _isActive = isActive; }
	void SetisLive(bool isLive) { _isLive = isLive; }
	// ��ǥ, ������, ��Ʈ, �ǹ��� ��ȭ�� �����
	// RECT�� �ٽ� �׷��־�� �Ѵ�.
	void SetPosition(POINTFLOAT position);
	void SetSize(POINTFLOAT size);
	void SetRect(RECT rc);
	void SetPivot(Pivot pivot);

	// ���� ������Ʈ �׾���.
	void Destroy() { this->_isLive = false; }

	// pivot�� ���� RECT�� �ٸ��� �׷��ش�. F12 ����
	void UpdateRectByPivot();
};

