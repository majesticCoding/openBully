#pragma once
#include "patcher.h"

class CTimer {
public:
	static void Initialise(void);
	static void Update(bool flag);
	static void Stop(void);
	static void Suspend(void);
	static void Resume(void);
	static void Shutdown(void);
	static void StartUserPause(void);
	static void EndUserPause(void);
	static uint32_t GetFrameDurationInMilliseconds(void);
	static float GetFrameDurationInSeconds(void);

	static void InjectHooks(void);

	static uint32_t &m_snTimeInMilliseconds;
	static uint32_t &m_snPreviousTimeInMilliseconds;
	static uint32_t &m_snTimeInMillisecondsNonClipped;
	static int32_t &dword_C1A9B8;
	static bool &m_CodePause;
	static bool &m_UserPause;
	static bool &m_WinPause;
	static bool &m_bTimeCorrection;
	static bool &m_bTimerStopped;
	static float &ms_fTimeScale;
	static float &ms_fTimeStep;
};

class TimeTracker {

};