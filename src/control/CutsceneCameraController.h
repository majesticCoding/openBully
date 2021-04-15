#pragma once
#include "patcher.h"

class CutsceneCameraController {
public:
	void Unload(void);
};

extern CutsceneCameraController *g_CutsceneCameraController;