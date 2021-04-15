#include "CutsceneCameraController.h"

CutsceneCameraController *g_CutsceneCameraController = reinterpret_cast<CutsceneCameraController *>(0xC3CFC4);

void CutsceneCameraController::Unload(void) {
	XCALL(0x4F7AC0);
}