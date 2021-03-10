#pragma once
#include "patcher.h"

class SeasonManager {
public:
	int32_t m_nChapter;
	int32_t field_4;
	int32_t field_8;
	static int32_t m_chapterSeasonTable[7];

	SeasonManager(void);
	~SeasonManager();

	static void SetSeasonalPedModels(int32_t);
	static void SetChapter(uint8_t);
};