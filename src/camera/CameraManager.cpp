#include "hook.h"
#include "CameraManager.h"

CameraManager *g_CameraManager = reinterpret_cast<CameraManager *>(0xC3CC68);

int32_t CameraManager::GetScreenFadeStatus(void) {
	XCALL(0x4F12F0);
}

void CameraManager::Reset(void) {
	XCALL(0x4F3720);
}

void CameraManager::SetRwCamera(RwCamera *pRwCamera) {
	XCALL(0x4F1800);
}