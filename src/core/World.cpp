#include "hook.h"
#include "World.h"

bool &CWorld::bProcessCutsceneOnly = *(bool*)0xC1AE6E;

CPlayerInfo &CWorld::Player = *(CPlayerInfo*)0xC1AEA8;

void CWorld::ClearExcitingStuffFromArea(CVector const &pos, float area, bool flag) {
	XCALL(0x45EC50);
}

void CWorld::Remove(CEntity *pEnt) {
	XCALL(0x45DD70);
}