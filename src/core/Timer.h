#pragma once
#include <windows.h>
#include "patcher.h"

class CTimer {
public:
	static void Initialise(void);
	static void Update(bool bParam);
	static void Stop(void);
	static void Suspend(void);
	static void Resume(void);
	static void Shutdown(void);
	static void StartUserPause(void);
	static void EndUserPause(void);
	static uint32_t GetFrameDurationInMilliseconds(void);
	static bool GetIsSlowMotionActive(void);
	static bool GetIsPauesed(void);
	static float GetFrameDurationInSeconds(void);
	static double GetPerformanceFrequency(void);

	static void InjectHooks(void);

	static uint32_t &m_snTimeInMilliseconds;
	static uint32_t &m_snPreviousTimeInMilliseconds;
	static uint32_t &m_snTimeInMillisecondsNonClipped;
	static uint32_t &m_FrameCounter;
	static int32_t &m_CodePause_SingleStepCounter;
	static int32_t &m_snTimeInMillisecondsPauseMode;
	static int32_t &m_GameMilliseconds;
	static int32_t &m_GameSeconds;
	static int32_t &m_GameMinutes;
	static int32_t &m_GameHours;
	static int64_t &sm_nPrevUpdateTimeInCycles;
	static int64_t &sm_GameStartTime;
	static int64_t &m_snFrameTimeInCycles;
	static int64_t &sm_LastCycleCount;
	static bool &m_CodePause;
	static bool &m_UserPause;
	static bool &m_WinPause;
	static bool &m_bTimeCorrection;
	static bool &m_bTimerStopped;
	static bool &m_CodePause_DoSingleStep;
	static float &ms_fTimeScale;
	static float &ms_fTimeStep;
	static float &ms_fTimeStepNonClipped;
};

class TimeTracker {

};