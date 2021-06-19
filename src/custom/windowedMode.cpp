#include "windowedMode.h"

RECT Size = { 300, 200, 1100, 800 };
using tProcWMMessage = bool(__stdcall*)(unsigned int);
tProcWMMessage procWMMessage = nullptr;

unsigned long hookedProcWM(bool stat) {
	return false;
}

void InjectCall(DWORD _offset, DWORD target)
{
	unsigned long Protection;
	VirtualProtect((void*)_offset, 5, PAGE_EXECUTE_READWRITE, &Protection);
	target -= (_offset + 5);
	*((unsigned char*)_offset) = 0xE8;
	memcpy((LPVOID)(_offset + 1), &target, sizeof(DWORD));
	VirtualProtect((void*)_offset, 5, Protection, 0);
}

void WindowedModePatch(void*) {
	while (true)
	{
		Sleep(350);
		HWND hWND = nullptr;
		if ((hWND = *reinterpret_cast<HWND*>(0xBD77FC)) != nullptr) {
			unsigned long oldProt = NULL;

			void *addr = reinterpret_cast<void*>(0x405F47);
			VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &oldProt);
			*reinterpret_cast<unsigned char*>(addr) = 0x09;
			VirtualProtect(addr, 1, oldProt, NULL);
			procWMMessage = reinterpret_cast<tProcWMMessage>(0x405DB0);

			InjectCall(0x401106, (DWORD)&hookedProcWM);

			SetWindowLong(hWND, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
			SetWindowLong(hWND, GWL_EXSTYLE, 0L);
			ShowWindow(hWND, SW_SHOWDEFAULT);
			MoveWindow(hWND, Size.left, Size.top, Size.right - Size.left, Size.bottom - Size.top, true);

			break;
		}
	}
	_endthread();
}