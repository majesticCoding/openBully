#include "Game.h"

HUDRadar *CGame::m_pRadar = *(HUDRadar **)0xC674CC;

void CGame::DrasticTidyUpMemory(bool) {
	XCALL(0x4304E0);
}