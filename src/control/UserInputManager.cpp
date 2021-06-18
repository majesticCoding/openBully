#include "UserInputManager.h"

UserInputManager *g_UserInputManager = reinterpret_cast<UserInputManager *>(0xA45A30);

void UserInputManager::SetInputEnabledFromCutscene(bool bParam) {
	XCALL(0x50DFB0);
}

void UserInputManager::SetInputEnabledFromAreaTransitions(bool bParam) {
	XCALL(0x50DFD0);
}