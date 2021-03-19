#pragma once
#include "patcher.h"
#include "Radar.h"

class CGame {
public:
	static HUDRadar *m_pRadar;
	static void DrasticTidyUpMemory(bool);
};