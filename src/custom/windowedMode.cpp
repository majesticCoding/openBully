// https://github.com/4el0ve4ik/BullyWindowedMode
#include <windows.h>
#include <process.h>

#include "hook.h"
#include "windowedMode.h"

RECT Size = { 300, 200, 1100, 800 };

unsigned long hookedProcWM(bool stat) {
	return 0;
}

void WindowedModePatch(void*) {
	HWND hWND = nullptr;
	while ((hWND = memory::read<HWND>(0xBD77FC)) == nullptr)
		Sleep(350);

	memory::write<unsigned char>(0x405F46 + 1, SW_RESTORE);
	memory::hook::inject_hook(0x401106, &hookedProcWM, memory::hook::HookType::Call);

	SetWindowLong(hWND, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	SetWindowLong(hWND, GWL_EXSTYLE, 0L);
	ShowWindow(hWND, SW_SHOWDEFAULT);
	MoveWindow(hWND, Size.left, Size.top, Size.right - Size.left, Size.bottom - Size.top, true);

	_endthread();
}