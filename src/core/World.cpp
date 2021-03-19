#include "World.h"

int32_t &CWorld::Player = *(int32_t*)0xC1AEA8;

void CWorld::ClearExcitingStuffFromArea(CVector const &pos, float radius, bool flag) {
	XCALL(0x45EC50);
}