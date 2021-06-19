// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <stdio.h>
#include "Game.h"
#include "CutsceneMgr.h"
#include "MissionMgr.h"
#include "ClassSchedule.h"
#include "Matrix.h"
#include "Clock.h"
#include "Timer.h"
#include "Occlusion.h"
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
	CGame::InjectHooks();
	CVector::InjectHooks();
	CMatrix::InjectHooks();
	CTimer::InjectHooks();
	Clock::InjectHooks();
	CCutsceneMgr::InjectHooks();
	CMissionMgr::InjectHooks();
	CClassSchedule::InjectHooks();
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
