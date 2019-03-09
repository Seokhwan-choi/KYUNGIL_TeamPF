#pragma once
#include "gameNode.h"
class GameObject : public gameNode
{
public: 
	// enum class 로 pivot 상태 등록
	// pivot에 따라 RECT 생성 기준점을 잡음
	enum class Pivot : int
	{
		LeftTop,		// RectMake
		Center,			// RectMakeCeter
		Bottom			// RectMakeBottom
	};

protected:
	// protected로 멤버변수
	// 상속관계에서만 사용가능
	string _name;					// 게임오브젝트 이름
	Pivot _pivot;					// 게임오브젝트 피벗(RECT를 그리는 기준점)
	POINTFLOAT _position;			// 게임오브젝트 좌표
	POINTFLOAT _size;				// 게임오브젝트 크기
	RECT _rc;						// 게임오브젝트 RECT
	bool _isActive;					// 게임오브젝트 활성화되있냐?
	bool _isLive;					// 게임오브젝트 살아있냐?
public:
	// 게임오브젝트 생성자를 통해서 멤버변수 초기화 해준다.
	GameObject(string name,POINTFLOAT pos,POINTFLOAT size,Pivot pivot);
	GameObject(string name);
	~GameObject();

	// virtual를 붙여주어 자식들이 override(재정의) 해서 사용 할 수 있게
	// gameNode에 가보아도 virtual 적혀있다.
	// 게임오브젝트 상속받은 클래스는 override 적어주고 사용
	// ex) void Init() override;
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(); 


	// 각 멤버변수에 대한 get을 만들어준다.
	string GetName()const { return this->_name; }
	POINTFLOAT GetPosition()const { return this->_position; }
	POINTFLOAT GetSize()const { return this->_size; }
	RECT GetRect()const { return this->_rc; }
	bool GetActive()const { return this->_isActive; }
	bool GetLive()const { return this->_isLive; }
	// 각 멤버변수에 대한 set을 만들어준다.
	void SetName(string name) { _name = name; }
	void SetisActive(bool isActive) { _isActive = isActive; }
	void SetisLive(bool isLive) { _isLive = isLive; }
	// 좌표, 사이즈, 렉트, 피벗에 변화가 생기면
	// RECT를 다시 그려주어야 한다.
	void SetPosition(POINTFLOAT position);
	void SetSize(POINTFLOAT size);
	void SetRect(RECT rc);
	void SetPivot(Pivot pivot);

	// 게임 오브젝트 죽었다.
	void Destroy() { this->_isLive = false; }

	// pivot에 따라 RECT를 다르게 그려준다. F12 ㄱㄱ
	void UpdateRectByPivot();
};

