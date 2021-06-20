#pragma once
#include "Vector.h"
#include "PlayerInfo.h"
#include "Entity.h"

class CWorld {
public:
	static CPlayerInfo &Player;
	static bool &bProcessCutsceneOnly;
	static void ClearExcitingStuffFromArea(CVector const &pos, float area, bool flag);
	static void Remove(CEntity *pEnt);
};