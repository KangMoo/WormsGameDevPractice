#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commdlg.h>	//OPENFILENAME


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "txtData.h"
#include "collision.h"
#include "database.h"

#include "tinyxml2.h"

using namespace std;
using namespace IOTA_UTIL;

using namespace tinyxml2;

//===============================================
// ## 윈도우 설정 디파인 ## 2017.07. 28 ##
//===============================================

#define WINNAME (LPTSTR)(TEXT("Iota Team"))
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define INIDATA iniDataManager::getSingleton()
#define DATABASE database::getSingleton()

//==================================
// ## 매크로 함수 ## 17.08.07 ##
//==================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//===================================
// ## 전역 변수 ## 17.08.07 ##
//===================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;