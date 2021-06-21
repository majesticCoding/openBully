#include <Windows.h>

#include "hook.h"
#include "Timer.h"

uint32_t &CTimer::m_snTimeInMilliseconds = *(uint32_t*)0xC1A9B4;
uint32_t &CTimer::m_snPreviousTimeInMilliseconds = *(uint32_t*)0xC1A9AC;
uint32_t &CTimer::m_snTimeInMillisecondsNonClipped = *(uint32_t*)0xC1A9B0;
int32_t &CTimer::m_CodePause_SingleStepCounter = *(int32_t*)0xC1AA00;
uint32_t &CTimer::m_FrameCounter = *(uint32_t*)0xC1A99C;
int32_t &CTimer::m_snTimeInMillisecondsPauseMode = *(int32_t*)0xA14A50;
int32_t &CTimer::m_GameMilliseconds = *(int32_t*)0xC1A9FC;
int32_t &CTimer::m_GameSeconds = *(int32_t*)0xC1A9F8;
int32_t &CTimer::m_GameHours = *(int32_t*)0xC1A9F0;
int32_t &CTimer::m_GameMinutes = *(int32_t*)0xC1A9F4;
int64_t &CTimer::sm_nPrevUpdateTimeInCycles = *(int64_t*)0xC1A9C8;
int64_t &CTimer::sm_GameStartTime = *(int64_t*)0xC1A9D8;
int64_t &CTimer::m_snFrameTimeInCycles = *(int64_t*)0xC1A9C0;
int64_t &CTimer::sm_LastCycleCount = *(int64_t*)0xC1A9D0;
bool &CTimer::m_WinPause = *(bool*)0xC1A998;
bool &CTimer::m_CodePause = *(bool*)0xC1A999;
bool &CTimer::m_UserPause = *(bool*)0xC1A99A;
bool &CTimer::m_bTimerStopped = *(bool*)0xC1A9E8;
bool &CTimer::m_bTimeCorrection = *(bool*)0xA14A4C;
bool &CTimer::m_CodePause_DoSingleStep = *(bool*)0xC1A9E9;
float &CTimer::ms_fTimeScale = *(float*)0xC1A9A8;
float &CTimer::ms_fTimeStep = *(float*)0xC1A9A4;
float &CTimer::ms_fTimeStepNonClipped = *(float*)0xC1A9A0;

int64_t &dFrequency = *(int64_t*)0xC1A9E0; //dbl_C1A9E0
uint32_t &suspendDepth = *(uint32_t*)0xC1A9B8; //dword_C1A9B8

void CTimer::InjectHooks(void) {
	using namespace memory::hook;

	inject_hook(0x45B8A0, &CTimer::Initialise);
	inject_hook(0x45B960, &CTimer::Update);
	inject_hook(0x45B800, &CTimer::Stop);
	inject_hook(0x45B7B0, &CTimer::Suspend);
	inject_hook(0x45B7D0, &CTimer::Resume);
	inject_hook(0x45B810, &CTimer::StartUserPause);
	inject_hook(0x45B820, &CTimer::EndUserPause);
	inject_hook(0x45B830, &CTimer::GetFrameDurationInMilliseconds);
	inject_hook(0x45B840, &CTimer::GetFrameDurationInSeconds);
	inject_hook(0x45BCA0, &CTimer::GetCurrentTimeInMilleseconds);
}

void CTimer::Initialise(void) {
	m_snTimeInMillisecondsNonClipped = 0;
	ms_fTimeScale = 1.0f;
	ms_fTimeStep = 1.0f;
	m_UserPause = false;
	m_CodePause = false;
	m_WinPause = false;
	m_snPreviousTimeInMilliseconds = 0;
	suspendDepth = 0;
	m_bTimeCorrection = true;
	m_snTimeInMilliseconds = 0;

	LARGE_INTEGER PerformanceCount;
	if (QueryPerformanceCounter(&PerformanceCount))
	{
		sm_nPrevUpdateTimeInCycles = PerformanceCount.QuadPart;
		sm_GameStartTime = PerformanceCount.QuadPart;
	}

	LARGE_INTEGER Frequency;
	if (QueryPerformanceFrequency(&Frequency))
		dFrequency = Frequency.QuadPart;

	m_snFrameTimeInCycles = 0;
	sm_LastCycleCount = 0;
	m_FrameCounter = 0; 

	printf("CTimer was initialized!\n");
}

void Platform_PadStopAllVibration(void) {
	XCALL(0x738780);
}

void CTimer::Update(bool bParam) {
	if (m_CodePause_DoSingleStep)
	{
		if (m_CodePause_SingleStepCounter <= 0)
		{
			m_CodePause = true;
			m_CodePause_SingleStepCounter = 0;
		}
		else
		{
			m_CodePause_SingleStepCounter -= 1;
			m_CodePause = false;
		}
	}

	if (suspendDepth == 0) {
		Stop();

		LARGE_INTEGER PerformanceCount;
		if (!m_bTimerStopped && QueryPerformanceCounter(&PerformanceCount))
			sm_LastCycleCount = PerformanceCount.QuadPart;

		int64_t timeDiff = sm_LastCycleCount - sm_nPrevUpdateTimeInCycles;
		sm_nPrevUpdateTimeInCycles = sm_LastCycleCount;
		m_snFrameTimeInCycles = timeDiff;
		m_snTimeInMillisecondsPauseMode += timeDiff / (GetPerformanceFrequency() / 1000);

		if (GetIsPaused() && !bParam)
		{
			m_snFrameTimeInCycles = 0;
			Platform_PadStopAllVibration();
		}
		
		double freq = GetPerformanceFrequency() / 1000;
		long double scaledFrameTime = m_snFrameTimeInCycles * ms_fTimeScale;

		PerformanceCount.QuadPart = scaledFrameTime / freq;
		m_snTimeInMilliseconds += PerformanceCount.LowPart;
		m_snTimeInMillisecondsNonClipped += PerformanceCount.QuadPart;
		ms_fTimeStep = scaledFrameTime / (freq * 20.0f);
		
		int64_t nTotalMilliseconds = (int64_t)((scaledFrameTime / freq) + m_GameMilliseconds);
		m_GameMilliseconds = nTotalMilliseconds % 1000;

		int64_t nTotalSeconds = ((nTotalMilliseconds / 1000) + m_GameSeconds);
		m_GameSeconds = nTotalSeconds % 60;
		m_GameHours += ((nTotalSeconds / 60) + m_GameMinutes) / 60;
		m_GameMinutes = ((nTotalSeconds / 60) + m_GameMinutes) % 60;

		if (ms_fTimeStep < 0.5f && !GetIsPaused() && !GetIsSlowMotionActive()) 
			ms_fTimeStep = 0.5f;

		ms_fTimeStepNonClipped = ms_fTimeStep;

		if (m_bTimeCorrection) {
			ms_fTimeStep = min(3.0f, ms_fTimeStep);

			if (GetFrameDurationInMilliseconds() > 60)
				m_snTimeInMilliseconds = m_snPreviousTimeInMilliseconds + 60;
		}

		m_FrameCounter++;
	}
}

void CTimer::Shutdown(void) {
	; //empty
}

void CTimer::Stop(void) {
	m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
}

void CTimer::StartUserPause(void) {
	m_UserPause = true;
}

void CTimer::EndUserPause(void) {
	m_UserPause = false;
}

inline uint32_t CTimer::GetFrameDurationInMilliseconds(void) {
	return m_snTimeInMilliseconds - m_snPreviousTimeInMilliseconds;
}

int64_t CTimer::GetPerformanceFrequency(void) {
	return dFrequency;
}

inline bool CTimer::GetIsSlowMotionActive(void) {
	return ms_fTimeScale < 1.0f;
}

float CTimer::GetFrameDurationInSeconds(void) {
	return (float)(GetFrameDurationInMilliseconds() / 1000.0);
}

void CTimer::Suspend(void) {
	suspendDepth += 1;
	if (suspendDepth <= 1)
		m_bTimerStopped = true;
}

void CTimer::Resume(void) {
	suspendDepth -= 1;
	if (suspendDepth == 0)
		m_bTimerStopped = false;
}

bool CTimer::GetIsPaused(void) {
	return m_UserPause || m_CodePause || m_WinPause;
}

uint32_t CTimer::GetCurrentTimeInMilleseconds(void) {
	LARGE_INTEGER PerformanceCount;

	return QueryPerformanceCounter(&PerformanceCount) ?
		(PerformanceCount.QuadPart - sm_GameStartTime) / (GetPerformanceFrequency() / 1000.0) : 1;
}