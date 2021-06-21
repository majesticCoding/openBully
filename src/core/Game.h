#pragma once
#include <cstdint>

#include "Radar.h"

class CGame {
public:
	static HUDRadar *m_pRadar;
	static char const *aDatFile;
	static int32_t currLevel;
	static int32_t currArea;

	static void Initialise(char const *);
	static void DrasticTidyUpMemory(bool);

	static void InjectHooks(void);
};