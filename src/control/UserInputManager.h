#pragma once

class UserInputManager {
public:
	void SetInputEnabledFromCutscene(bool bParam);
	void SetInputEnabledFromAreaTransitions(bool bParam);
};

extern UserInputManager *g_UserInputManager;