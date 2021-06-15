#pragma once
#include "patcher.h"
#include "RwCamera.h"

class CameraManager {
public:
	int32_t GetScreenFadeStatus(void);
	void Reset(void);
	void SetRwCamera(RwCamera *pRwCamera);
};

extern CameraManager *g_CameraManager;