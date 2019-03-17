#include "stdafx.h"
#include "loading.h"
#include "LoadingScene.h"
#include "GameCompleteUi.h"
#include "stage1StartUi.h"

HRESULT LoadingScene::Init(void)
{
	_loading = new loading;
	_loading->init();

	//stage1StartUi* _stage1startui = new stage1StartUi("stage1startui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _stage1startui);
	//
	//GameCompleteUi* _gamecompleteui = new GameCompleteUi("gamecompleteui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	//OBJECTMANAGER->AddObject(ObjectType::UI, _gamecompleteui);

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
		SCENEMANAGER->ChangeScene("����ȭ��"); //����������, ���Ͻ�������, ������������
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
	_loading->loadFrameImage("����ⷷ", "Background/����ⷷ2.bmp", 19568, 278, 8, 1);
	_loading->loadFrameImage("���庮", "Background/���庮.bmp", 5400, 960, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��", "Background/�볪��.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	_loading->loadImage("���", "Background/���.bmp", 14070, 1150, true, RGB(255, 0, 255));
	_loading->loadImage("����ǹ��", "Background/����ǹ��.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_loading->loadImage("����ȼ�", "Background/����ȼ�.bmp", 14070, 1150, true, RGB(255, 0, 255));
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
	_loading->loadFrameImage("cap_granade", "UI/item/item_1.bmp",899,55, 7, 1, true, RGB(255, 0, 255));
	_loading->loadImage("heavy", "UI/item/item_2.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("granade", "UI/item/item_3.bmp", 50, 50, true, RGB(255, 0, 255));

	//�÷��̾�� ���� �� ��������� ��������
	_loading->loadFrameImage("heavy_dis", "UI/item/item_4.bmp", 100, 20, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish", "UI/item/item_5.bmp", 540, 60, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chicken", "UI/item/item_6.bmp", 1364, 50, 11, 1, true, RGB(255, 0, 255));
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
	//for (int i = 0; i < 14; i++) {
	//	string num = to_string(i + 1);
	//	string temp = "UI/stage1StartScene/number";
	//	string end = ".bmp";
	//	string name = temp + num;
	//	string fullName = name + end;
	//	_loading->loadImage(name, fullName.c_str(),((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].x,
	//		((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].y, 79, 109, true, RGB(255, 0, 255));
	//}
	////���ø�Ʈ
	//for (int i = 0; i < 17; i++) {
	//	string num = to_string(i + 1);
	//	string temp = "UI/missioncomplete/number";
	//	string end = ".bmp";
	//	string name = temp + num;
	//	string fullName = name + end;
	//	_loading->loadImage(name, fullName.c_str(),((GameCompleteUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gamecompleteui"))->getSite()[i].x,
	//		((GameCompleteUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "gamecompleteui"))->getSite()[i].y,79, 109, true, RGB(255, 0, 255));
	//}


	//=============================================================
	//	## UI end##
	//=============================================================

	//=============================================================
	//	## Monster start##
	//=============================================================

	//=============================================================
	//	##���ڸ�##
	//=============================================================
	_loading->loadFrameImage("flybug", "Enemy/���ڸ��⺻.bmp", 8400, 400, 24, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug1", "Enemy/���ڸ���ġ��.bmp", 9450, 400, 27, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug2", "Enemy/���ڸ�����.bmp", 10500, 200, 30, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug3", "Enemy/���ڸ���������.bmp", 1560, 120, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug4", "Enemy/���ڸ���������2.bmp", 1560, 120, 13, 1, true, RGB(255, 0, 255));

	//=============================================================
	//	##�����##
	//=============================================================
	_loading->loadFrameImage("fish1", "Enemy/�����-1.bmp", 1200, 60, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish2", "Enemy/�����-2.bmp", 2400, 60, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish3", "Enemy/�����-3.bmp", 1300, 60, 13, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##������##
	//=============================================================
	_loading->loadFrameImage("crab", "Enemy/����(��)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab1", "Enemy/����(��)-2(������).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab2", "Enemy/����(��)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab3", "Enemy/����(��)-3(������).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab4", "Enemy/����(��)-6.bmp", 3300, 194, 22, 1, true, RGB(250, 2, 250));
	_loading->loadFrameImage("crab5", "Enemy/����(��)-6(������).bmp", 3300, 194, 22, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##��ǰ��##
	//=============================================================
	_loading->loadFrameImage("bubblecrab", "Enemy/����(��)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab2", "Enemy/����(��)-2(������).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab3", "Enemy/����(��)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab4", "Enemy/����(��)-3(������).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab5", "Enemy/����(��)-6.bmp", 3300, 194, 22, 1, true, RGB(250, 2, 250));
	_loading->loadFrameImage("bubblecrab6", "Enemy/����(��)-6(������).bmp", 3300, 194, 22, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab7", "Enemy/����(��)-4.bmp", 1808, 150, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab8", "Enemy/����(��)-4(������).bmp", 1808, 150, 13, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##ū��##
	//=============================================================
	_loading->loadFrameImage("bigcrab", "Enemy/�����Ա⺻.bmp", 3500, 850, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab2", "Enemy/�������̵�.bmp", 5992, 850, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab3", "Enemy/�����԰���.bmp", 3000, 850, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab4", "Enemy/�����԰�ǰ����.bmp", 4500, 850, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab5", "Enemy/����������.bmp", 6000, 850, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab6", "Enemy/�����Ի����.bmp", 11500, 850, 23, 2, true, RGB(255, 0, 255));
	//=============================================================
	//	##����##
	//=============================================================
	_loading->loadFrameImage("boss", "Enemy/�����⺻.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss1", "Enemy/�������ָ�.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss2", "Enemy/��������.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss3", "Enemy/���������ı⺻.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss4", "Enemy/���������ĺ��ָ�.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss5", "Enemy/�����׾��.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss6", "Enemy/����������.bmp", 15840, 1060, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("deathwater", "Enemy/������.bmp", 2600, 400, 26, 1, true, RGB(255, 0, 255));

	//=============================================================
	//	## Monster end##
	//=============================================================
#pragma endregion

#pragma region player

	// ========================================== �÷��̾� �̹��� =======================================================
	_loading->loadFrameImage("�÷��̾��", "�÷��̾�/�÷��̾��.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾���Ѱ���", "�÷��̾�/�⺻���Ѱ���.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��̵�", "�÷��̾�/�÷��̾��̵�.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾������Ѱ���", "�÷��̾�/���⺻���Ѱ���.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾�⺻����", "�÷��̾�/�÷��̾�⺻����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��������", "�÷��̾�/�÷��̾��������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��ޱ׷�", "�÷��̾�/�÷��̾��ޱ׷�.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��ޱ׷����̵�", "�÷��̾�/�÷��̾��ޱ׷����̵�.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��ޱ׷�����", "�÷��̾�/�÷��̾��ޱ׷�����.bmp", 3200, 805, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��¿��̵��ϸ�����", "�÷��̾�/�÷��̾��¿��̵��ϸ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��̵��ϸ����", "�÷��̾�/�÷��̾��̵��ϸ����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾����������", "�÷��̾�/�÷��̾����������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�", "�÷��̾�/�÷��̾��̵��ϸ鼭�����ϰ��������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));//�߻��ϴ°� 
	_loading->loadFrameImage("�÷��̾������ϸ鼭����", "�÷��̾�/�÷��̾������ϸ鼭����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾�������������", "�÷��̾�/�÷��̾�������������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��̵��ϸ���������", "�÷��̾�/�÷��̾��̵��ϸ���������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾�������߾Ʒ�����", "�÷��̾�/�÷��̾�������߾Ʒ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾��̵������߾Ʒ�����", "�÷��̾�/�÷��̾��̵������߾Ʒ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));

	//����ź
	_loading->loadFrameImage("�÷��̾��̵�����ź", "�÷��̾�/�÷��̾��̵�����ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾������ź������", "�÷��̾�/�÷��̾������ź������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�÷��̾����������ź", "�÷��̾�/�÷��̾����������ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));


	//�غ�ӽŰ�   // 160���� �����Ѵ� 
	_loading->loadFrameImage("�غ񰡸�", "�÷��̾�/�غ񰡸�.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));//�����Ⱦ� render�� �������� 
	_loading->loadFrameImage("�غ��̵��ϸ����", "�÷��̾�/�غ��̵��ϸ����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ񰡸���������", "�÷��̾�/�غ񰡸���������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ񰡸�����", "�÷��̾�/�غ񰡸�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ��̵���������", "�÷��̾�/�غ��̵���������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ񰡸�����", "�÷��̾�/�غ񰡸�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ�Ʒ�����", "�÷��̾�/�غ�Ʒ�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ�Ʒ�����", "�÷��̾�/�غ�Ʒ�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ�Ʒ��̵�", "�÷��̾�/�غ�Ʒ��̵�.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ��̵��ϸ�����", "�÷��̾�/�غ��̵��ϸ�����.bmp", 1600, 805, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ��̵�", "�÷��̾�/�غ��̵�.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ��̵�����", "�÷��̾�/�غ��̵�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ񰡸�����", "�÷��̾�/�غ񰡸�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ������", "�÷��̾�/�غ������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�غ񰡸��Ʒ���������", "�÷��̾�/�غ񰡸��Ʒ���������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ������߾Ʒ�������", "�÷��̾�/�غ������߾Ʒ�������.bmp", 1920, 402, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�غ�ɾƼ�����ź", "�÷��̾�/�غ�ɾƼ�����ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));

	_loading->loadImage("���ϻ�", "�÷��̾�/���ϻ�.bmp", 320, 403, true, RGB(255, 0, 255));

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

	_loading->loadSound("��ǰ������", "SOUND/����/��ǰ������.mp3", false, false);
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
