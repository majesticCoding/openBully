#include "hook.h"
#include "PlayerInfo.h"

CVector CPlayerInfo::GetPos(void) {
	XCALL(0x4468B0);
}

void CPlayerInfo::MakePlayerSafe(bool bState) {
	XCALL(0x445DA0);
}

bool FindPlayerIsMovingTooFast(void) {
	XCALL(0x4469A0);
}

CVector FindPlayerCoors(void) {
	XCALL(0x446900);
}

float FindPlayerHeading(void) {
	XCALL(0x446A80);
}