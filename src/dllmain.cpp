// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <process.h>
#include <stdio.h>

#include "Game.h"
#include "CutsceneMgr.h"
#include "MissionMgr.h"
#include "ClassSchedule.h"
#include "Matrix.h"
#include "Clock.h"
#include "Timer.h"
#include "Occlusion.h"
#include "SimpleTransform.h"
#include "MatrixLink.h"
#include "Placeable.h"
#include "Rect.h"
#include "Entity.h"
#include "BaseModelInfo.h"
#include "SplineInterpolater.h"
#include "TextParser.h"

#include "windowedMode.h"

#pragma warning(disable:4996)

void DisplayConsole(void)
{
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
}

void InjectHooks(void) {
	// core
	Clock::InjectHooks();
	CGame::InjectHooks();
	CMatrixLink::InjectHooks();
	CPlaceable::InjectHooks();
	CSimpleTransform::InjectHooks();
	CTimer::InjectHooks();
	TextParser::InjectHooks();

	// entities
	CEntity::InjectHooks();

	// math
	CMatrix::InjectHooks();
	CRect::InjectHooks();
	CVector::InjectHooks();
	SplineInterpolater::InjectHooks();

	//modelinfo
	//CBaseModelInfo::InjectHooks();
	
	// animation
	CCutsceneMgr::InjectHooks();

	// scripts
	CMissionMgr::InjectHooks();
	CMissionRunInst::InjectHooks();
	
	// classes
	CClassSchedule::InjectHooks();

	// render
	COcclusion::InjectHooks();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisplayConsole();
#ifdef WINDOWED_MODE
		_beginthread(WindowedModePatch, 0, NULL);
#endif
		InjectHooks();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
