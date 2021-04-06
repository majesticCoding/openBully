#pragma once
#include "patcher.h"

class CameraManager {
public:
	int32_t GetScreenFadeStatus(void);
	void Reset(void);
};

extern CameraManager *g_CameraManager;