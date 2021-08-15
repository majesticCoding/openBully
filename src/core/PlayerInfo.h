#pragma once
#include "Vector.h"
#include "PlayerPed.h"
#include "ColModel.h"

enum ScriptSaveDataEnum {
	UPGRADE_28 = 28
};

class CPlayerInfo {
public:
	CPlayerPed *m_pPed;
	CColModel model;

	CVector GetPos(void);
	void MakePlayerSafe(bool bState);
	void SetUnlockPlayerUpgrade(ScriptSaveDataEnum eType, int missionId);
};

bool FindPlayerIsMovingTooFast(void);
float FindPlayerHeading(void);
CVector FindPlayerCoors(void);