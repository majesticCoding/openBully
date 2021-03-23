#include "World.h"

CPlayerInfo &CWorld::Player = *(CPlayerInfo*)0xC1AEA8;

void CWorld::ClearExcitingStuffFromArea(CVector const &pos, float radius, bool flag) {
	XCALL(0x45EC50);
}