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
		SCENEMANAGER->ChangeScene("시작화면"); //스테이지원, 지하스테이지, 보스스테이지
	}
}

void LoadingScene::Render(void)
{
	_loading->render();
}


void LoadingScene::LoadingImage()
{
	// ===============================================================================================
	// ################# 지상 스테이지 이미지 ###########################################################
	// ===============================================================================================
	_loading->loadFrameImage("배경출렁", "Background/배경출렁2.bmp", 19568, 278, 8, 1);
	_loading->loadFrameImage("맵장벽", "Background/맵장벽.bmp", 5400, 960, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("통", "Background/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	_loading->loadImage("배경", "Background/배경.bmp", 14070, 1150, true, RGB(255, 0, 255));
	_loading->loadImage("배경의배경", "Background/배경의배경.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_loading->loadImage("배경픽셀", "Background/배경픽셀.bmp", 14070, 1150, true, RGB(255, 0, 255));
	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================




	// ===============================================================================================
	// ################# 지하 스테이지 이미지 ###########################################################
	// ===============================================================================================

	_loading->loadImage("지하배경", "BackGround/지하베이스.bmp", 6774, 958);
	_loading->loadImage("지하배경픽셀", "BackGround/지하베이스픽셀.bmp", 6774, 958);
	_loading->loadFrameImage("통나옴", "BackGround/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addImage("지하배경", "BackGround/지하베이스.bmp", 6774, 958);
	//IMAGEMANAGER->addImage("지하배경픽셀", "BackGround/지하베이스픽셀.bmp", 6774, 958);
	//IMAGEMANAGER->addFrameImage("통나옴", "BackGround/통나옴.bmp", 7392, 384, 22, 1, true, RGB(255, 0, 255));
	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================


	// ===============================================================================================
	// ################# 보스전 이미지 #################################################################
	// ===============================================================================================

	_loading->loadImage("보스배경", "BackGround/보스배경.bmp", 2555, 958);
	_loading->loadFrameImage("보스출렁", "BackGround/보스출렁.bmp", 10240, 100, 8, 1);
	_loading->loadImage("곧부서짐", "BackGround/곧부서짐.bmp", 875, 183);


	//IMAGEMANAGER->addImage("보스배경", "BackGround/보스배경.bmp", 2555, 958);
	//IMAGEMANAGER->addFrameImage("보스출렁", "BackGround/보스출렁.bmp", 10240, 100, 8, 1);
	// ===============================================================================================
	// ###############################################################################################
	// ===============================================================================================



#pragma region ui
	//=============================================================
	//	## UI start##
	//=============================================================
	
	// ===============================================================================================
	// ################# 시작 이미지 #################################################################
	// ===============================================================================================
	_loading->loadFrameImage("startScene", "UI/startScene/MetalSlugMainSceneImg.bmp", 2560, 960, 2, 1);

	
	// ===============================================================================================
	// ################# 선택 이미지 #################################################################
	// ===============================================================================================
	_loading->loadImage("choiceimage", "UI/choiceScene/character_main.bmp", 1280, 960, true, RGB(255, 0, 255));
	_loading->loadFrameImage("timenumber", "UI/choiceScene/scoreNumber.bmp", 500, 48, 10, 1, true, RGB(0, 248, 0));
	_loading->loadImage("door", "UI/choiceScene/door.bmp", 271, 535, true, RGB(255, 0, 255));

	//캐릭터 선택 되지 않았을 시  나오는 이미지 선언
	_loading->loadImage("characterblack1", "UI/choiceScene/marco_black.bmp", 271, 535);
	_loading->loadImage("characterblack2", "UI/choiceScene/eri_black.bmp", 271, 535);
	_loading->loadImage("characterblack3", "UI/choiceScene/tarma_black.bmp", 271, 535);
	_loading->loadImage("characterblack4", "UI/choiceScene/pio_black.bmp", 271, 535);

	//버튼으로 캐릭터 선택창 이미지 바뀌는것 선언
	_loading->loadImage("charactercolor1", "UI/choiceScene/marco_color.bmp", 271, 535);
	_loading->loadImage("charactercolor2", "UI/choiceScene/eri_color.bmp", 271, 535);
	_loading->loadImage("charactercolor3", "UI/choiceScene/tarma_color.bmp", 271, 535);
	_loading->loadImage("charactercolor4", "UI/choiceScene/pio_color.bmp", 271, 535);

	//선택된 캐릭터 이미지 선언해주기 - 테스트
	_loading->loadImage("characterchoice1", "UI/choiceScene/marco_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice2", "UI/choiceScene/eri_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice3", "UI/choiceScene/tarma_choice.bmp", 271, 514);
	_loading->loadImage("characterchoice4", "UI/choiceScene/pio_choice.bmp", 271, 514);

	//p1노란색 빨간색
	_loading->loadFrameImage("yellowred", "UI/choiceScene/yellow_p2.bmp", 244, 77, 2, 1, true, RGB(255, 0, 255));
	//캐릭터 선택 후 문이 내려오면서 캐릭터 움직임 보여줄 이미지
	_loading->loadFrameImage("downcharacter", "UI/choiceScene/down_tarma.bmp", 1084, 535, 4, 1, true, RGB(255, 0, 255));



	// ===============================================================================================
	// ################# 타임 및 플레이어 데이터 이미지 #################################################################
	// ===============================================================================================
	_loading->loadFrameImage("제한시간", "UI/timenumber.bmp", 510, 69, 10.1, true, RGB(255, 0, 255));

	_loading->loadImage("bombarms", "UI/PlayerStateRegardingPicture/armsbomb.bmp", 261, 72, true, RGB(255, 0, 255));
	_loading->loadImage("guagebar", "UI/PlayerStateRegardingPicture/guageBar.bmp", 222, 35, true, RGB(255, 0, 255));
	_loading->loadImage("1up", "UI/PlayerStateRegardingPicture/1up=.bmp", 123, 36, true, RGB(255, 0, 255));
	_loading->loadImage("infinite", "UI/infinite.bmp", 80, 30, true, RGB(255, 0, 255));

	_loading->loadFrameImage("lifescore", "UI/playerlife.bmp", 380, 36, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("score", "UI/PlayerStateRegardingPicture/점수 숫자.bmp", 340, 34, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bombscore", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("armsImg", "UI/playerlife.bmp", 380, 30, 10, 1, true, RGB(255, 0, 255));


	_loading->loadImage("만세", "UI/save.bmp", 35, 36, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# 최종 점수 이미지 #################################################################
	// ===============================================================================================
	_loading->loadImage("점수틀", "UI/점수틀.bmp", 555, 656, true, RGB(255, 0, 255));
	_loading->loadImage("모두의이름", "UI/모두의 이름.bmp", 490, 228, true, RGB(255, 0, 255));
	_loading->loadFrameImage("포로오른쪽", "UI/item/captive_sirR.bmp", 2916, 150, 14, 1, true, RGB(255, 0, 255));
	_loading->loadImage("x", "UI/x.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage("만", "UI/10000.bmp", 161, 35, true, RGB(255, 0, 255));
	_loading->loadFrameImage("구한포로수", "UI/playerlife.bmp", 660, 60, 10, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# 아이템 이미지 #################################################################
	// ===============================================================================================
	//플레이어와 닿기 전
	_loading->loadFrameImage("cap_granade", "UI/item/item_1.bmp",899,55, 7, 1, true, RGB(255, 0, 255));
	_loading->loadImage("heavy", "UI/item/item_2.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("granade", "UI/item/item_3.bmp", 50, 50, true, RGB(255, 0, 255));

	//플레이어와 닿은 후 사라지도록 만들어야함
	_loading->loadFrameImage("heavy_dis", "UI/item/item_4.bmp", 100, 20, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish", "UI/item/item_5.bmp", 540, 60, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chicken", "UI/item/item_6.bmp", 1364, 50, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fuit", "UI/item/item_7.bmp", 389, 38, 12, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# 포로 이미지 #################################################################
	// ===============================================================================================
	//포로
	_loading->loadFrameImage("tied", "UI/item/captive_tied.bmp", 1872, 150, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("untied", "UI/item/captive_untied.bmp", 2080, 150, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("walk", "UI/item/captive_walk.bmp", 2500, 300, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("run", "UI/item/captive_run.bmp", 1666, 150, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("sir", "UI/item/captive_sir.bmp", 2916, 150, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("item", "UI/item/captive_item.bmp", 2288, 150, 11, 1, true, RGB(255, 0, 255));
	//루미
	_loading->loadFrameImage("rumi_walk", "UI/item/rumi_walk.bmp", 3328, 150, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_run", "UI/item/rumi_run.bmp", 1872, 150, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_sir", "UI/item/rumi_sir.bmp", 832, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rumi_crush", "UI/item/rumi_crush.bmp", 2288, 150, 11, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// ################# 종료 이미지 #################################################################
	// ===============================================================================================
	//중앙 컨티뉴 이미지
	_loading->loadImage("continue", "UI/gameOverScene/continue.bmp", 653, 79, true, RGB(255, 0, 255));
	_loading->loadFrameImage("number", "UI/gameOverScene/gameOverNumberCenter.bmp", 2120, 234, 10, 1, true, RGB(0, 248, 0));
	_loading->loadFrameImage("gameover", "UI/gameOverScene/gameOverScene.bmp", 2560, 960, 2, 1, true, RGB(255, 0, 255));


	// ===============================================================================================
	// #################스타트 및 컴플리트 이미지 #################################################################
	// ===============================================================================================
	//스타트
	//for (int i = 0; i < 14; i++) {
	//	string num = to_string(i + 1);
	//	string temp = "UI/stage1StartScene/number";
	//	string end = ".bmp";
	//	string name = temp + num;
	//	string fullName = name + end;
	//	_loading->loadImage(name, fullName.c_str(),((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].x,
	//		((stage1StartUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "stage1startui"))->getSite()[i].y, 79, 109, true, RGB(255, 0, 255));
	//}
	////컴플리트
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
	//	##잠자리##
	//=============================================================
	_loading->loadFrameImage("flybug", "Enemy/잠자리기본.bmp", 8400, 400, 24, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug1", "Enemy/잠자리덮치기.bmp", 9450, 400, 27, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug2", "Enemy/잠자리죽음.bmp", 10500, 200, 30, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug3", "Enemy/잠자리날개파편.bmp", 1560, 120, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flybug4", "Enemy/잠자리날개파편2.bmp", 1560, 120, 13, 1, true, RGB(255, 0, 255));

	//=============================================================
	//	##물고기##
	//=============================================================
	_loading->loadFrameImage("fish1", "Enemy/물고기-1.bmp", 1200, 60, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish2", "Enemy/물고기-2.bmp", 2400, 60, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fish3", "Enemy/물고기-3.bmp", 1300, 60, 13, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##근접게##
	//=============================================================
	_loading->loadFrameImage("crab", "Enemy/몬스터(게)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab1", "Enemy/몬스터(게)-2(오른쪽).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab2", "Enemy/몬스터(게)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab3", "Enemy/몬스터(게)-3(오른쪽).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("crab4", "Enemy/몬스터(게)-6.bmp", 3300, 194, 22, 1, true, RGB(250, 2, 250));
	_loading->loadFrameImage("crab5", "Enemy/몬스터(게)-6(오른쪽).bmp", 3300, 194, 22, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##거품게##
	//=============================================================
	_loading->loadFrameImage("bubblecrab", "Enemy/몬스터(게)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab2", "Enemy/몬스터(게)-2(오른쪽).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab3", "Enemy/몬스터(게)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab4", "Enemy/몬스터(게)-3(오른쪽).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab5", "Enemy/몬스터(게)-6.bmp", 3300, 194, 22, 1, true, RGB(250, 2, 250));
	_loading->loadFrameImage("bubblecrab6", "Enemy/몬스터(게)-6(오른쪽).bmp", 3300, 194, 22, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab7", "Enemy/몬스터(게)-4.bmp", 1808, 150, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bubblecrab8", "Enemy/몬스터(게)-4(오른쪽).bmp", 1808, 150, 13, 1, true, RGB(255, 0, 255));
	//=============================================================
	//	##큰게##
	//=============================================================
	_loading->loadFrameImage("bigcrab", "Enemy/붉은게기본.bmp", 3500, 850, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab2", "Enemy/붉은게이동.bmp", 5992, 850, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab3", "Enemy/붉은게공격.bmp", 3000, 850, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab4", "Enemy/붉은게거품공격.bmp", 4500, 850, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab5", "Enemy/붉은게죽음.bmp", 6000, 850, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bigcrab6", "Enemy/붉은게사라짐.bmp", 11500, 850, 23, 2, true, RGB(255, 0, 255));
	//=============================================================
	//	##보스##
	//=============================================================
	_loading->loadFrameImage("boss", "Enemy/보스기본.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss1", "Enemy/보스불주먹.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss2", "Enemy/보스변신.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss3", "Enemy/보스변신후기본.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss4", "Enemy/보스변신후불주먹.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss5", "Enemy/보스죽어욧.bmp", 7920, 1060, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss6", "Enemy/보스터져욧.bmp", 15840, 1060, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("deathwater", "Enemy/물보라.bmp", 2600, 400, 26, 1, true, RGB(255, 0, 255));

	//=============================================================
	//	## Monster end##
	//=============================================================
#pragma endregion

#pragma region player

	// ========================================== 플레이어 이미지 =======================================================
	_loading->loadFrameImage("플레이어가만", "플레이어/플레이어가만.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어딱총공격", "플레이어/기본딱총공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어이동", "플레이어/플레이어이동.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어위딱총공격", "플레이어/위기본딱총공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어기본점프", "플레이어/플레이어기본점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어가만위보기", "플레이어/플레이어가만위보기.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어쭈그려", "플레이어/플레이어쭈그려.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어쭈그려서이동", "플레이어/플레이어쭈그려서이동.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어쭈그려공격", "플레이어/플레이어쭈그려공격.bmp", 3200, 805, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어좌우이동하며점프", "플레이어/플레이어좌우이동하며점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어이동하며공격", "플레이어/플레이어이동하며공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어가만점프공격", "플레이어/플레이어가만점프공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어이동하면서점프하고위에발사", "플레이어/플레이어이동하면서점프하고위에모션.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));//발사하는것 
	_loading->loadFrameImage("플레이어점프하면서공격", "플레이어/플레이어점프하면서공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어점프중위공격", "플레이어/플레이어점프중위공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어이동하며위에공격", "플레이어/플레이어이동하며위에공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어가만점프중아래공격", "플레이어/플레이어가만점프중아래공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어이동점프중아래공격", "플레이어/플레이어이동점프중아래공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));

	//수류탄
	_loading->loadFrameImage("플레이어이동수류탄", "플레이어/플레이어이동수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어가만수류탄던지기", "플레이어/플레이어가만수류탄던지기.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("플레이어가만점프수류탄", "플레이어/플레이어가만점프수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));


	//해비머신건   // 160으로 고정한다 
	_loading->loadFrameImage("해비가만", "플레이어/해비가만.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));//아직안씀 render에 적긴적음 
	_loading->loadFrameImage("해비이동하며공격", "플레이어/해비이동하며공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비가만점프공격", "플레이어/해비가만점프공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비가만공격", "플레이어/해비가만공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비이동점프공격", "플레이어/해비이동점프공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비가만점프", "플레이어/해비가만점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비아래공격", "플레이어/해비아래공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비아래가만", "플레이어/해비아래가만.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비아래이동", "플레이어/해비아래이동.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비이동하며점프", "플레이어/해비이동하며점프.bmp", 1600, 805, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비이동", "플레이어/해비이동.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비이동업샷", "플레이어/해비이동업샷.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비가만업샷", "플레이어/해비가만업샷.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비고정용", "플레이어/해비고정용.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("해비가만아래점프공격", "플레이어/해비가만아래점프공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비점프중아래보고가만", "플레이어/해비점프중아래보고가만.bmp", 1920, 402, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("해비앉아서수류탄", "플레이어/해비앉아서수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));

	_loading->loadImage("낙하산", "플레이어/낙하산.bmp", 320, 403, true, RGB(255, 0, 255));

#pragma endregion

}

void LoadingScene::LoadingSound()
{

	// ===============================================================================================
	// ################################### 포로 사운드 삽입 ############################################
	// ===============================================================================================

	_loading->loadSound("포로떙큐", "SOUND/포로/포로땡큐.mp3", false, false);		// 포로 감사
	_loading->loadSound("포로충성", "SOUND/포로/포로감사.mp3", false, false);		// 포로 충성
	_loading->loadSound("가방포로", "SOUND/포로/가방포로.mp3", false, false);		// 가방포로(유미) 감사

	// ===============================================================================================
	// ################################### 선택 사운드 삽입 ############################################
	// ===============================================================================================
	
	_loading->loadSound("선택문열림", "SOUND/캐릭터선택/선택문열림.mp3", false, false);
	_loading->loadSound("선택문닫힘", "SOUND/캐릭터선택/선택문닫힘.mp3", false, false);
	_loading->loadSound("타마선택", "SOUND/캐릭터선택/타마선택.mp3", false, false);

	// ===============================================================================================
	// ################################### effect 사운드 삽입 ##########################################
	// ===============================================================================================

	_loading->loadSound("동전넣기", "SOUND/이펙트/동전넣기.mp3", false, false);
	_loading->loadSound("딱총", "SOUND/이펙트/딱총.mp3", false, false);
	_loading->loadSound("미션1시작", "SOUND/이펙트/미션1시작.mp3", false, false);
	_loading->loadSound("미션클리어", "SOUND/이펙트/미션클리어.mp3", false, false);
	_loading->loadSound("아이템먹음", "SOUND/이펙트/아이템먹음.mp3", false, false);
	_loading->loadSound("죽음", "SOUND/이펙트/죽음.mp3", false, false);
	//_loading->loadSound("칼질", "SOUND/이펙트/칼질.mp3", false, false);
	//_loading->loadSound("칼질2", "SOUND/이펙트/칼질2.mp3", false, false);
	_loading->loadSound("헤비먹음", "SOUND/이펙트/헤비먹음.mp3", false, false);
	_loading->loadSound("헤비발사", "SOUND/이펙트/헤비발사.mp3", false, false);
	_loading->loadSound("장벽부서짐", "SOUND/이펙트/장벽부서짐.mp3", false, false);

	// ===============================================================================================
	// ################################### 몬스터 사운드 삽입 ###########################################
	// ===============================================================================================

	_loading->loadSound("거품게죽음", "SOUND/몬스터/거품게죽음.mp3", false, false);
	_loading->loadSound("거품공격", "SOUND/몬스터/거품공격.mp3", false, false);
	_loading->loadSound("몬스터총맞음", "SOUND/몬스터/몬스터총맞음.mp3", false, false);
	_loading->loadSound("물고기죽음", "SOUND/몬스터/물고기죽음.mp3", false, false);
	_loading->loadSound("보스게부숨", "SOUND/몬스터/보스게부숨.mp3", false, false);
	_loading->loadSound("보스게죽음", "SOUND/몬스터/보스게죽음.mp3", false, false);
	_loading->loadSound("보스페이즈2", "SOUND/몬스터/보스페이즈2.mp3", false, false);
	_loading->loadSound("작은게죽음", "SOUND/몬스터/작은게죽음.mp3", false, false);
	_loading->loadSound("잠자리죽음", "SOUND/몬스터/잠자리죽음.mp3", false, false);
	_loading->loadSound("큰게죽음", "SOUND/몬스터/큰게죽음.mp3", false, false);

	// ===============================================================================================
	// #################################### BGM 사운드 삽입 ###########################################
	// ===============================================================================================

	_loading->loadSound("보스전시작", "SOUND/브금/보스전시작.mp3", true, true);
	_loading->loadSound("선택", "SOUND/브금/선택.mp3", true, true);
	_loading->loadSound("선택전", "SOUND/브금/선택전.mp3", true, true);
	_loading->loadSound("스테이지시작", "SOUND/브금/스테이지시작.mp3", true, true);
	_loading->loadSound("지하시작", "SOUND/브금/지하시작.mp3", true, true);
	
}
