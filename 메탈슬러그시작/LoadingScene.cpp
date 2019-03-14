#include "stdafx.h"
#include "loading.h"
#include "LoadingScene.h"
#include "GameCompleteUi.h"
#include "stage1StartUi.h"

HRESULT LoadingScene::Init(void)
{
	_loading = new loading;
	_loading->init();

	this->LoadingSound();
	this->LoadingImage();

	return S_OK;
}

void LoadingScene::Release(void)
{
	//_loading->release();
	//SAFE_DELETE(_loading);
}

void LoadingScene::Update(void)
{
	_loading->update();
	if (_loading->loadingDone())
	{
		SCENEMANAGER->ChangeScene("����ȭ��");
	}
}

void LoadingScene::Render(void)
{
	_loading->render();
}


void LoadingScene::LoadingImage()
{
	// ===============================================================================================
	// ################# ���� �������� �̹��� ###########################################################
	// ===============================================================================================




	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================




	// ===============================================================================================
	// ################# ���� �������� �̹��� ###########################################################
	// ===============================================================================================

	_loading->loadImage("���Ϲ��", "BackGround/���Ϻ��̽�.bmp", 6774, 958);
	_loading->loadImage("���Ϲ���ȼ�", "BackGround/���Ϻ��̽��ȼ�.bmp", 6774, 958);
	_loading->loadFrameImage("�볪��", "BackGround/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addImage("���Ϲ��", "BackGround/���Ϻ��̽�.bmp", 6774, 958);
	//IMAGEMANAGER->addImage("���Ϲ���ȼ�", "BackGround/���Ϻ��̽��ȼ�.bmp", 6774, 958);
	//IMAGEMANAGER->addFrameImage("�볪��", "BackGround/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================


	// ===============================================================================================
	// ################# ������ �̹��� #################################################################
	// ===============================================================================================

	_loading->loadImage("�������", "BackGround/�������.bmp", 2555, 958);
	_loading->loadFrameImage("�����ⷷ", "BackGround/�����ⷷ.bmp", 10240, 100, 8, 1);
	_loading->loadImage("��μ���", "BackGround/��μ���.bmp", 875, 183);


	//IMAGEMANAGER->addImage("�������", "BackGround/�������.bmp", 2555, 958);
	//IMAGEMANAGER->addFrameImage("�����ⷷ", "BackGround/�����ⷷ.bmp", 10240, 100, 8, 1);
	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================



#pragma region ui
	//=============================================================
	//	## UI start##
	//=============================================================
	
	// ===============================================================================================
	// ################# ���� �̹��� #################################################################
	// ===============================================================================================
	_loading->loadFrameImage("startScene", "UI/startScene/MetalSlugMainSceneImg.bmp", 2560, 960, 2, 1);

	
	// ===============================================================================================
	// ################# ���� �̹��� #################################################################
	// ===============================================================================================
	_loading->loadImage("choiceimage", "UI/choiceScene/character_main.bmp", 1280, 960, true, RGB(255, 0, 255));
	_loading->loadFrameImage("timenumber", "UI/choiceScene/scoreNumber.bmp", 500, 48, 10, 1, true, RGB(0, 248, 0));
	_loading->loadImage("door", "UI/choiceScene/door.bmp", 271, 535, true, RGB(255, 0, 255));

	//ĳ���� ���� ���� �ʾ��� ��  ������ �̹��� ����
	_loading->loadImage("characterblack1", "UI/choiceScene/marco_black.bmp", 271, 535);
	_loading->loadImage("characterblack2", "UI/choiceScene/eri_black.bmp", 271, 535);
	_loading->loadImage("characterblack3", "UI/choiceScene/tarma_black.bmp", 271, 535);
	_loading->loadImage("characterblack4", "UI/choiceScene/pio_black.bmp", 271, 535);

	//��ư���� ĳ���� ����â �̹��� �ٲ�°� ����
	_loading->loadImage("charactercolor1", "UI/choiceScene/marco_color.bmp", 271, 535);
	_loading->loadImage("charactercolor2", "UI/choiceScene/eri_color.bmp", 271, 535);
	_loading->loadImage("charactercolor3", "UI/choiceScene/tarma_color.bmp", 271, 535);
	_loading->loadImage("charactercolor4", "UI/choiceScene/pio_color.bmp", 271, 535);

	//���õ� ĳ���� �̹��� �������ֱ� - �׽�Ʈ
	_loading->loadImage("characterchoice1", "UI/choiceScene/marco_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice2", "UI/choiceScene/eri_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice3", "UI/choiceScene/tarma_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice4", "UI/choiceScene/pio_choice.bmp", 271, 514);

	//p1����� ������
	_loading->loadFrameImage("yellowred", "UI/choiceScene/yellow_p2.bmp", 244, 77, 2, 1, true, RGB(255, 0, 255));
	//ĳ���� ���� �� ���� �������鼭 ĳ���� ������ ������ �̹���
	_loading->loadFrameImage("downcharacter", "UI/choiceScene/down_tarma.bmp", 1084, 535, 4, 1, true, RGB(255, 0, 255));



	// ===============================================================================================
	// ################# Ÿ�� �� �÷��̾� ������ �̹��� #################################################################
	// ===============================================================================================
	_loading->loadFrameImage("���ѽð�", "UI/timenumber.bmp", 510, 69, 10.1, true, RGB(255, 0, 255));

	_loading->loadImage("bombarms", "UI/PlayerStateRegardingPicture/armsbomb.bmp", 261, 72, true, RGB(255, 0, 255));
	_loading->loadImage("guagebar", "UI/PlayerStateRegardingPicture/guageBar.bmp", 222, 35, true, RGB(255, 0, 255));
	_loading->loadImage("1up", "UI/PlayerStateRegardingPicture/1up=.bmp", 123, 36, true, RGB(255, 0, 255));
	_loading->loadImage("infinite", "UI/infinite.bmp", 80, 30, true, RGB(255, 0, 255));

	_loading->loadFrameImage("lifescore", "UI/playerlife.bmp", 380, 36, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("score", "UI/PlayerStateRegardingPicture/���� ����.bmp", 340, 34, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bombscore", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("armsImg", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));


	_loading->loadImage("����", "UI/save.bmp", 35, 36, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# ���� ���� �̹��� #################################################################
	// ===============================================================================================
	_loading->loadImage("����Ʋ", "UI/����Ʋ.bmp", 555, 656, true, RGB(255, 0, 255));
	_loading->loadImage("������̸�", "UI/����� �̸�.bmp", 490, 228, true, RGB(255, 0, 255));
	_loading->loadFrameImage("���ο�����", "UI/item/captive_sirR.bmp", 2916, 150, 14, 1, true, RGB(255, 0, 255));
	_loading->loadImage("x", "UI/x.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage("��", "UI/10000.bmp", 161, 35, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�������μ�", "UI/playerlife.bmp", 660, 60, 10, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# ������ �̹��� #################################################################
	// ===============================================================================================
	//�÷��̾�� ��� ��
	_loading->loadFrameImage("cap_granade", "UI/item/item_1.bmp", 7, 1, true, RGB(255, 0, 255));
	_loading->loadImage("heavy", "UI/item/item_2.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("granade", "UI/item/item_3.bmp", 50, 50, true, RGB(255, 0, 255));

	//�÷��̾�� ���� �� ��������� ��������
	_loading->loadFrameImage("heavy_dis", "UI/item/item_4.bmp", 100, 20, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish", "UI/item/item_5.bmp", 540, 60, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chicken", "UI/item/item_6.bmp", 341, 32, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fuit", "UI/item/item_7.bmp", 389, 38, 12, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# ���� �̹��� #################################################################
	// ===============================================================================================
	//����
	_loading->loadFrameImage("tied", "UI/item/captive_tied.bmp", 1872, 150, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("untied", "UI/item/captive_untied.bmp", 2080, 150, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("walk", "UI/item/captive_walk.bmp", 2500, 300, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("run", "UI/item/captive_run.bmp", 1666, 150, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("sir", "UI/item/captive_sir.bmp", 2916, 150, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("item", "UI/item/captive_item.bmp", 2288, 150, 11, 1, true, RGB(255, 0, 255));
	//���
	_loading->loadFrameImage("rumi_walk", "UI/item/rumi_walk.bmp", 3328, 150, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_run", "UI/item/rumi_run.bmp", 1872, 150, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_sir", "UI/item/rumi_sir.bmp", 832, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_crush", "UI/item/rumi_crush.bmp", 2288, 150, 11, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# ���� �̹��� #################################################################
	// ===============================================================================================
	//�߾� ��Ƽ�� �̹���
	_loading->loadImage("continue", "UI/gameOverScene/continue.bmp", 653, 79, true, RGB(255, 0, 255));
	_loading->loadFrameImage("number", "UI/gameOverScene/gameOverNumberCenter.bmp", 2120, 234, 10, 1, true, RGB(0, 248, 0));
	_loading->loadFrameImage("gameover", "UI/gameOverScene/gameOverScene.bmp", 2560, 960, 2, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// #################��ŸƮ �� ���ø�Ʈ �̹��� #################################################################
	// ===============================================================================================
	//��ŸƮ
	for (int i = 0; i < 14; i++) {
		string num = to_string(i + 1);
		string temp = "UI/stage1StartScene/number";
		string end = ".bmp";
		string name = temp + num;
		string fullName = name + end;
		_loading->loadImage(name, fullName.c_str(),((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].x,
			((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].y, 79, 109, true, RGB(255, 0, 255));
	}
	//���ø�Ʈ
	for (int i = 0; i < 17; i++) {
		string num = to_string(i + 1);
		string temp = "UI/missioncomplete/number";
		string end = ".bmp";
		string name = temp + num;
		string fullName = name + end;
		_loading->loadImage(name, fullName.c_str(),((GameCompleteUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gamecompleteui"))->getSite()[i].x,
			((GameCompleteUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gamecompleteui"))->getSite()[i].y,79, 109, true, RGB(255, 0, 255));
	}


	//=============================================================
	//	## UI end##
	//=============================================================
#pragma endregion
}

void LoadingScene::LoadingSound()
{

	// ===============================================================================================
	// ################################### ���� ���� ���� ############################################
	// ===============================================================================================

	_loading->loadSound("���΋�ť", "SOUND/����/���ζ�ť.mp3", false, false);		// ���� ����
	_loading->loadSound("�����漺", "SOUND/����/���ΰ���.mp3", false, false);		// ���� �漺
	_loading->loadSound("��������", "SOUND/����/��������.mp3", false, false);		// ��������(����) ����

	// ===============================================================================================
	// ################################### ���� ���� ���� ############################################
	// ===============================================================================================
	
	_loading->loadSound("���ù�����", "SOUND/ĳ���ͼ���/���ù�����.mp3", false, false);
	_loading->loadSound("���ù�����", "SOUND/ĳ���ͼ���/���ù�����.mp3", false, false);
	_loading->loadSound("Ÿ������", "SOUND/ĳ���ͼ���/Ÿ������.mp3", false, false);

	// ===============================================================================================
	// ################################### effect ���� ���� ##########################################
	// ===============================================================================================

	_loading->loadSound("�����ֱ�", "SOUND/����Ʈ/�����ֱ�.mp3", false, false);
	_loading->loadSound("����", "SOUND/����Ʈ/����.mp3", false, false);
	_loading->loadSound("�̼�1����", "SOUND/����Ʈ/�̼�1����.mp3", false, false);
	_loading->loadSound("�̼�Ŭ����", "SOUND/����Ʈ/�̼�Ŭ����.mp3", false, false);
	_loading->loadSound("�����۸���", "SOUND/����Ʈ/�����۸���.mp3", false, false);
	_loading->loadSound("����", "SOUND/����Ʈ/����.mp3", false, false);
	//_loading->loadSound("Į��", "SOUND/����Ʈ/Į��.mp3", false, false);
	//_loading->loadSound("Į��2", "SOUND/����Ʈ/Į��2.mp3", false, false);
	_loading->loadSound("������", "SOUND/����Ʈ/������.mp3", false, false);
	_loading->loadSound("���߻�", "SOUND/����Ʈ/���߻�.mp3", false, false);
	_loading->loadSound("�庮�μ���", "SOUND/����Ʈ/�庮�μ���.mp3", false, false);

	// ===============================================================================================
	// ################################### ���� ���� ���� ###########################################
	// ===============================================================================================

	_loading->loadSound("��ǰ����", "SOUND/����/��ǰ����.mp3", false, false);
	_loading->loadSound("�����Ѹ���", "SOUND/����/�����Ѹ���.mp3", false, false);
	_loading->loadSound("���������", "SOUND/����/���������.mp3", false, false);
	_loading->loadSound("�����Ժμ�", "SOUND/����/�����Ժμ�.mp3", false, false);
	_loading->loadSound("����������", "SOUND/����/����������.mp3", false, false);
	_loading->loadSound("����������2", "SOUND/����/����������2.mp3", false, false);
	_loading->loadSound("����������", "SOUND/����/����������.mp3", false, false);
	_loading->loadSound("���ڸ�����", "SOUND/����/���ڸ�����.mp3", false, false);
	_loading->loadSound("ū������", "SOUND/����/ū������.mp3", false, false);

	// ===============================================================================================
	// #################################### BGM ���� ���� ###########################################
	// ===============================================================================================

	_loading->loadSound("����������", "SOUND/���/����������.mp3", true, true);
	_loading->loadSound("����", "SOUND/���/����.mp3", true, true);
	_loading->loadSound("������", "SOUND/���/������.mp3", true, true);
	_loading->loadSound("������������", "SOUND/���/������������.mp3", true, true);
	_loading->loadSound("���Ͻ���", "SOUND/���/���Ͻ���.mp3", true, true);
	
}
