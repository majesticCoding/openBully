#pragma once
#include "patcher.h"
#include "Vector.h"
#include "PlayerInfo.h"

class CWorld {
public:
	static int32_t &Player;
	static void ClearExcitingStuffFromArea(CVector const &pos, float radius, bool flag);
};