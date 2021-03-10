#pragma once
#include "patcher.h"

class Clock {
public:
	static uint32_t	&ms_nMillisecondsPerGameMinute;
	static uint32_t	&ms_nLastClockTick;
	static uint8_t &ms_nGameClockHours;
	static uint8_t &ms_nGameClockMinutes;
	static uint16_t	&ms_nGameClockSeconds;
	static uint8_t &ms_Stored_nGameClockHours;
	static uint8_t &ms_Stored_nGameClockMinutes;
	static uint16_t	&ms_Stored_nGameClockSeconds;
	static bool &bClockHasBeenStored;
	static bool &m_bPaused;
	static bool &m_bForcePauseThroughLua;
	static int32_t &ms_nEnableMissionIndex;
	static bool &m_bDoTheTimeWarp;
	static uint32_t &ms_iDaysPassed;
	static uint32_t &ms_nMillisecondsPerGameMinuteOnMission;
	static uint32_t &ms_nMillisecondsPerGameMinuteOffMission;

	static void Initialise(uint32_t scale);
	static void RestoreClock(void);
	static void StoreClock(void);
	static bool IsDayTime(void);
	static bool IsNightTime(void);
	static void ForcePauseThroughLua(bool bPauseflag);
	static void SetGameClock(uint8_t h, uint8_t m);
	static void IncrementClock(uint32_t m);
	static uint32_t GetGameClockMinutesUntil(uint8_t, uint8_t);
	static void DeterminePauseState(void);
	static void Update(void);
	static bool GetIsTimeInRange(uint32_t h1, uint32_t h2, uint32_t m1, uint32_t m2);
	static void AdvanceToNightTime(void);

	static void InjectHooks(void);
};