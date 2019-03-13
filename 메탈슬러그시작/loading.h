#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "SceneMaker.h"
//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================

//�ε������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//���Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,			//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,			//�Ϲ� �̹���(��ġ��ǥ)
	LOAD_KIND_FRAMEIMAGE_0,		//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,		//������ �̹���(��ġ��ǥ)
	LOAD_KIND_SOUND,			//����
	LOAD_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;				//�̹��� Ű��
	const char* fileName;		//�����̸�
	int x, y;					//��ġ��ǥ
	int width, height;			//����, ����ũ��
	int frameX, frameY;			//������ x,y
	bool trans;					//����������?
	COLORREF transColor;		//�������?
};

struct tagSoundResource
{
	string keyName;				//�̹���Ű��
	const char* fileName;		//���� �̸�
	bool bgm;					//������� ����
	bool loop;					//�������� ����
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;

public:
	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(string keyName, int width, int height);
	//�̹��� ���� �ʱ�ȭ(�ֻ��)
	HRESULT init(string keyName, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���� �ʱ�ȭ(�ֻ��)
	HRESULT init(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//���� �ε�
	HRESULT init(string keyName, const char* fileName, bool bgm, bool loop);

	//�ε������� ���� ��������
	LOAD_KIND getLoadingKind() { return _kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource() { return _imageResource; }
	tagSoundResource getSoundResource() { return _soundResource; }

	loadItem() {}
	~loadItem() {}
};


//=============================================================
//	## loading ## (�ε� Ŭ����)
//=============================================================
class loading : public gameNode
{
private:
	//�ε� ������ Ŭ������ ���� ���� �� �ݺ���
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	image* _bgImage;	// �ε� ��׶��� �̹���
	//�̺κ��� �ε�ȭ�鿡�� ����� �̹����� �ε���
	progressBar* _loadingBar;
	int _currentGauge;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	//�� ��Ʈ�� �ʱ�ȭ
	void loadImage(string keyName, int width, int height);
	//�̹��� ���� �ʱ�ȭ(�ֻ��)
	void loadImage(string keyName, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���� �ʱ�ȭ(�ֻ��)
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//���� �ε��Լ�
	void loadSound(string keyName, const char* fileName, bool bgm = false, bool loop = false);


	/*�߿���*/
	//�ε��Ϸ� �Ƴ�? (�ε��Ϸ��� ȭ����ȯ)
	BOOL loadingDone();

	//�ε������ Ŭ������ ���� ���� ��������
	arrLoadItem getLoadItem() { return _vLoadItem; }
	int getCurrentGauge() { return _currentGauge; }

	loading() {}
	~loading() {}
};
