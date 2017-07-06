// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <commdlg.h>	//OPENFILENAME
#include <map>
#include <vector>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "txtData.h"
#include "itemDataBase.h"


// 게임전용 싱글톤
#include "inven.h"
#include "playerStatMemory.h"


using namespace std;
using namespace OMEGA_UTIL;


//==================================
// ## 2017.04.05 ## 디파인문 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("Symphony of Night"))
#define WINSTARTX 50			//윈도우 창 시작지점 X좌표
#define WINSTARTY 50			//윈도우 창 시작지점 Y좌표
#define WINSIZEX  800			//윈도우 창 가로크기
#define WINSIZEY  600			//윈도우 창 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//싱글톤 디파인
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define ITEM allItem::getSingleton()
#define TXTDATA txtData::getSingleton()

//게임 전용 디파인
#define INVEN inven::getSingleton()
#define ALUCARD alucardHave::getSingleton()
#define ALUCARD_INFO playerStatMemory::getSingleton()

//==================================
// ## 2017.04.05 ## 매크로 함수 ##
//==================================

#define SAFE_DELETE(p)	{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}

//==================================
// ## 2017.04.10 ## 전역 변수 ##
//==================================

extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern POINT _ptMouse;



//===============================================메모리 누수 체크============================
#ifndef _MEMORYLEAK_H_
#define _MEMORYLEAK_H_

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
static class MemoryMng
{
public:
	MemoryMng()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(3333);

		//만약 누수 경로가 명확히 뜨지 않을 경우 위의 주석된 줄을 활성화 후
		//누수 경고가 뜬 문장에 제시된 숫자를 괄호안에 넣고 디버깅하면 누수된 줄에 디버깅이 멈춘다
	}
	~MemoryMng()
	{
		_ASSERTE(_CrtCheckMemory());
	}


} MemoryLeak;
#endif      // _DEBUG
#endif      // _MEMORYLEAK_H_


//======================================================================================
// template safe delete 
template <typename T>
inline extern void safeDelete(T* &p)
{
	if (p == NULL) return;

	delete p;
	p = static_cast<T*>(NULL);
}


template <typename T>
inline extern void safeDeleteArray(T* &p)
{
	if (p == NULL) return;

	delete[] p;
	p = static_cast<T*>(NULL);
}