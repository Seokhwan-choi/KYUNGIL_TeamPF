#include "stdafx.h"
#include "imageManager.h"

#include "image.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� �̹����� �����Ѵٸ� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش��̹����� ����
	if (img) return img;

	//Ű������ ã�Ҵµ� �����ϱ� ���� ����
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������!!!
	//ù��° = Ű -> first
	//�ι�° = �� -> second
	//�����͸� �߰��Ҷ� �ݵ�� Ű,����� ������ �־�� �Ѵ�
	//pair, make_pair�� ����ؼ� �߰��Ѵ�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����Ѵٸ� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش��̹����� ����
	if (img) return img;

	//Ű������ ã�Ҵµ� �����ϱ� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������!!!
	//ù��° = Ű -> first
	//�ι�° = �� -> second
	//�����͸� �߰��Ҷ� �ݵ�� Ű,����� ������ �־�� �Ѵ�
	//pair, make_pair�� ����ؼ� �߰��Ѵ�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����Ѵٸ� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش��̹����� ����
	if (img) return img;

	//Ű������ ã�Ҵµ� �����ϱ� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������!!!
	//ù��° = Ű -> first
	//�ι�° = �� -> second
	//�����͸� �߰��Ҷ� �ݵ�� Ű,����� ������ �־�� �Ѵ�
	//pair, make_pair�� ����ؼ� �߰��Ѵ�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����Ѵٸ� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش��̹����� ����
	if (img) return img;

	//Ű������ ã�Ҵµ� �����ϱ� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������!!!
	//ù��° = Ű -> first
	//�ι�° = �� -> second
	//�����͸� �߰��Ҷ� �ݵ�� Ű,����� ������ �־�� �Ѵ�
	//pair, make_pair�� ����ؼ� �߰��Ѵ�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����Ѵٸ� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش��̹����� ����
	if (img) return img;

	//Ű������ ã�Ҵµ� �����ϱ� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������!!!
	//ù��° = Ű -> first
	//�ι�° = �� -> second
	//�����͸� �߰��Ҷ� �ݵ�� Ű,����� ������ �־�� �Ѵ�
	//pair, make_pair�� ����ؼ� �߰��Ѵ�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		//return key->first(Ű)
		return key->second;//��(�� �̹���Ŭ����)
	}

	//�˻��� Ű�� �̹����� ã�� ���ߴٸ� NULL����
	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �ش��̹��� ����
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	//�˻��� Ű�� �̹����� ã�� ���ߴٸ� NULL����
	return FALSE;
}

BOOL imageManager::deleteAll()
{
	//����ü�� ���鼭 �ϳ��� ���� �����
	mapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	for (; iter != _mImageList.end();)
	{
		//�̹����� ������ �̹��� Ŭ���� ����
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else//�̹��� ������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
	_mImageList.clear();

	return TRUE;
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ű�� ��
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
