// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

// Windows 헤더 파일:
#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>

// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

using namespace std;

#include <SDKDDKVer.h>
#include "util.h"
using namespace MY_UTIL;

//==============================================================//
//						내가만든 헤더파일							//
//==============================================================//
#include "CommomMacroFuntion.h"
#include "KeyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "Gizmo.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "CommonEnemyFrame.h"
#include "PlayerData.h"



//==============================================================//
//					## 싱글톤을 추가한다 ##					    //
//==============================================================//
#define KEYMANAGER KeyManager::getSingleton()		//키매니져 주는 싱글톤.
#define RND randomFunction::getSingleton()			//랜덤값 주는 싱글톤.
#define IMAGEMANAGER imageManager::getSingleton()
#define GIZMO Gizmo::getSingleton()
#define CAMERA Camera::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define OBJECTMANAGER ObjectManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define DATA PlayerData::getSingleton()


//==============================================================//
//				## 디파인문 ## (윈도우창 초기화)				    //
//==============================================================//
#define WINNAME			(LPTSTR)(TEXT(" 메탈슬러그3 제작자 : 석환, 병윤, 지연, 수완, 민병 "))
#define WINSTARTX		100
#define WINSTARTY		0
#define WINSIZEX		1280
#define WINSIZEY		958
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//==============================================================//
//		## 매크로함수 ## (클래스에서 동적할당된 부분 해제)				//
//==============================================================//
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//==============================================================//
//						## 전역변수 ##							//
//==============================================================//
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;