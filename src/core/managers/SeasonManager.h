#pragma once
#include <cstdint>

#define NUM_CHAPTERS 7

class SeasonManager {
public:
	int32_t m_nChapter;
	int32_t field_4;
	int32_t field_8;
	static int32_t m_chapterSeasonTable[NUM_CHAPTERS];

	SeasonManager(void);
	~SeasonManager();

	static void SetSeasonalPedModels(int32_t);
	static void SetChapter(uint8_t);
};

extern SeasonManager *g_SeasonManager;