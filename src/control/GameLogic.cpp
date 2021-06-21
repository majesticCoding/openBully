#include "hook.h"
#include "GameLogic.h"

CGameLogic &g_GameLogic = *reinterpret_cast<CGameLogic *>(0xBD1078);

void CGameLogic::Init(void) {
	XCALL(0x430640);
}