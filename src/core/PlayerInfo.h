#pragma once
#include "Vector.h"

class CPlayerInfo {
public:
	CVector GetPos(void);
	void MakePlayerSafe(bool bState);
};

bool FindPlayerIsMovingTooFast(void);
float FindPlayerHeading(void);
CVector FindPlayerCoors(void);