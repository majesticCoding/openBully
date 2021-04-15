#pragma once
#include "patcher.h"

class UserInputManager {
public:
	void SetInputEnabledFromCutscene(bool bParam);
};

extern UserInputManager *g_UserInputManager;