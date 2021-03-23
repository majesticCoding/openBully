#pragma once
#include "patcher.h"
#include "Vector.h"

class CPlayerInfo {
public:
	CVector GetPos(void);
};

bool FindPlayerIsMovingTooFast(void);
float FindPlayerHeading(void);
CVector FindPlayerCoors(void);