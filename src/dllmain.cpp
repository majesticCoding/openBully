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

#pragma warning(disable:4996)

int32_t *g_pMainApp = reinterpret_cast<int32_t *>(0xBF3838);

void DisplayConsole(void)
{
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
}

int32_t windowedModePatchBack = 0x43B798;

__declspec(naked) void windowedModePatch() {
	WNDCLASSA WndClass;

	WndClass.style = WS_POPUPWINDOW;
	WndClass.lpfnWndProc = (WNDPROC)0x82A010;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = (HINSTANCE)0xBD77B4;
	WndClass.hIcon = LoadIconA((HINSTANCE)0xBD77B4, (LPCSTR)0x65);
	WndClass.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName = "Gamebryo Application";

	if (*(LPCSTR*)(g_pMainApp + 48))
		WndClass.lpszMenuName = *(LPCSTR*)(g_pMainApp + 48);
	else
		WndClass.lpszMenuName = 0;

	RegisterClassA(&WndClass);

	__asm jmp windowedModePatchBack
}

int32_t windowedModePatch2Back = 0x82BAEC;

__declspec(naked) void windowedModePatch2() {
	__asm {
		mov     eax, 600
		push    eax
		mov     ecx, 800
		jmp windowedModePatch2Back
	}
}

int32_t CommandSelectRendererHook1Back = 0x829F27;

__declspec(naked) void CommandSelectRendererHook1() {
	__asm {
		mov [ecx + 0x34], 0
		jmp CommandSelectRendererHook1Back
	}
}

int32_t CommandSelectRendererHook2Back = 0x829F31;

__declspec(naked) void CommandSelectRendererHook2() {
	__asm {
		mov byte ptr[edx + 0x36], 1
		jmp CommandSelectRendererHook2Back
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

	//custom windowed mode hack
	/*HookInstall(0x43B722, windowedModePatch, 5);
	HookInstall(0x82BAE7, windowedModePatch2, 5);

	//looks like they don't work or wtf???
	HookInstall(0x829F24, CommandSelectRendererHook1, 5);
	HookInstall(0x829F2D, CommandSelectRendererHook2, 5);*/
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
		InjectHooks();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
