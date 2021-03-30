#include "Timer.h"

uint32_t &CTimer::m_snTimeInMilliseconds = *(uint32_t*)0xC1A9B4;
uint32_t &CTimer::m_snPreviousTimeInMilliseconds = *(uint32_t*)0xC1A9AC;
uint32_t &CTimer::m_snTimeInMillisecondsNonClipped = *(uint32_t*)0xC1A9B0;
int32_t &CTimer::dword_C1A9B8 = *(int32_t*)0xC1A9B8;
bool &CTimer::m_WinPause = *(bool*)0xC1A998;
bool &CTimer::m_CodePause = *(bool*)0xC1A999;
bool &CTimer::m_UserPause = *(bool*)0xC1A99A;
bool &CTimer::m_bTimerStopped = *(bool*)0xC1A9E8;
bool &CTimer::m_bTimeCorrection = *(bool*)0xA14A4C;
float &CTimer::ms_fTimeScale = *(float*)0xC1A9A8;
float &CTimer::ms_fTimeStep = *(float*)0xC1A9A4;


void CTimer::InjectHooks(void) {
	InjectHook(0x45B800, &CTimer::Stop, PATCH_JUMP);
	InjectHook(0x45B7B0, &CTimer::Suspend, PATCH_JUMP);
	InjectHook(0x45B7D0, &CTimer::Resume, PATCH_JUMP);
	InjectHook(0x45B810, &CTimer::StartUserPause, PATCH_JUMP);
	InjectHook(0x45B820, &CTimer::EndUserPause, PATCH_JUMP);
	InjectHook(0x45B830, &CTimer::GetFrameDurationInMilliseconds, PATCH_JUMP);
	InjectHook(0x45B840, &CTimer::GetFrameDurationInSeconds, PATCH_JUMP);
}

void CTimer::Initialise(void) {
	CTimer::m_snTimeInMillisecondsNonClipped = 0;
	CTimer::ms_fTimeScale = 1.0f;
	CTimer::ms_fTimeStep = 1.0f;
	m_UserPause = false;
	m_CodePause = false;
	m_WinPause = false;
	CTimer::m_snPreviousTimeInMilliseconds = 0;
	dword_C1A9B8 = 0;
	CTimer::m_bTimeCorrection = true;
	m_snTimeInMilliseconds = 0;

	//TODO: the rest
}

void CTimer::Update(bool flag) {
	; //TODO
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

float CTimer::GetFrameDurationInSeconds(void) {
	return (float)(GetFrameDurationInMilliseconds() / 1000.0);
}

void CTimer::Suspend(void) {
	dword_C1A9B8 += 1;
	if (dword_C1A9B8 <= 1)
		m_bTimerStopped = true;
}

void CTimer::Resume(void) {
	dword_C1A9B8 -= 1;
	if (dword_C1A9B8 == 0)
		m_bTimerStopped = false;
}