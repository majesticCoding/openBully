#pragma once
#include "Vector.h"
#include "PlayerPed.h"
#include "ColModel.h"

class CPlayerInfo {
public:
	CPlayerPed *m_pPed;
	CColModel model;

	CVector GetPos(void);
	void MakePlayerSafe(bool bState);
};

bool FindPlayerIsMovingTooFast(void);
float FindPlayerHeading(void);
CVector FindPlayerCoors(void);