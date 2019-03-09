#pragma once
#include "GameObject.h"
class Rect : public GameObject
{
private:

	int _count;				//계속 상승할 값(제한시간 낮추기 위한 변수)
	int _playTime;			//제한시간
	int _score;				//점수
	int _life;				//목숨
	int _bomb;				//수류탄갯수
	int _arms;				//총탄갯수 ->enum문으로해서 일반총일떈 무한으로 표시
							//헤비머신일땐 200으로 표시하도록 함
	image* _scoreImage;
	image* _timeImage;
	image* _lifeImage;
	image* _bombImage;
	image* _armsImage;
	image* _insertcoinImage;


public:
	
	Rect(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Rect();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

