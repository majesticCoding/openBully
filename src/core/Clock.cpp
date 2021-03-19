#include "Clock.h"
#include "Timer.h"
#include "CutsceneMgr.h"
#include "MissionMgr.h"
#include "ClassSchedule.h"
#include "TimeCycle.h"
#include "Hud.h"
#include "ActionTree.h"
#include "GlobalButes.h"
#include "WeaponInventory.h"
#include "World.h"

uint32_t &Clock::ms_nMillisecondsPerGameMinute = *(uint32_t*)0x9E51A4;
uint32_t &Clock::ms_nLastClockTick = *(uint32_t*)0xBCEB44;
uint8_t &Clock::ms_nGameClockHours = *(uint8_t*)0xBCEB4B;
uint8_t &Clock::ms_nGameClockMinutes = *(uint8_t*)0xBCEB4A;
uint16_t &Clock::ms_nGameClockSeconds = *(uint16_t*)0xBCEB48;
uint8_t	&Clock::ms_Stored_nGameClockHours = *(uint8_t*)0xBCEB3E;
uint8_t &Clock::ms_Stored_nGameClockMinutes = *(uint8_t*)0xBCEB3D;
uint16_t &Clock::ms_Stored_nGameClockSeconds = *(uint16_t*)0xBCEB40;
bool &Clock::bClockHasBeenStored = *(bool*)0xB9D885;
bool &Clock::m_bPaused = *(bool*)0xBCEB42;
bool &Clock::m_bForcePauseThroughLua = *(bool*)0xBCEB3F;
int32_t &Clock::ms_nEnableMissionIndex = *(int32_t*)0x9E51A0;
bool &Clock::m_bDoTheTimeWarp = *(bool*)0xBCEB3C;
uint32_t &Clock::ms_iDaysPassed	= *(uint32_t*)0xBCEB4C;
uint32_t &Clock::ms_nMillisecondsPerGameMinuteOnMission = *(uint32_t*)0x9E51A8;
uint32_t &Clock::ms_nMillisecondsPerGameMinuteOffMission = *(uint32_t*)0x9E51AC;

float &gNormalizedTime = *(float*)0xC66B20;
bool &gOverrideNormalizedTime = *(bool*)0xC66B24;
float &gOverridNormalizedTime = *(float*)0xC66B28;
uint8_t &g_SeasonManager = *(uint8_t*)0xA147E0;
int *g_Shop = reinterpret_cast<int(*)>(0xC18748);

bool &byte_B9DB1C = *(bool*)0xB9DB1C;
int32_t &dword_C3CD0C = *(int32_t*)0xC3CD0C;

auto SetGlobalNormTime = (void(__cdecl*)(void))(0x513030);
auto sub_425D60	= (bool(__thiscall*)(int32_t aShop[]))(0x425D60);

void Clock::InjectHooks(void) {
	InjectHook(0x426020, &Clock::Initialise, PATCH_JUMP);
	InjectHook(0x425FE0, &Clock::IsDayTime, PATCH_JUMP);
	InjectHook(0x426000, &Clock::IsNightTime, PATCH_JUMP);
	InjectHook(0x425F80, &Clock::StoreClock, PATCH_JUMP);
	InjectHook(0x425FB0, &Clock::RestoreClock, PATCH_JUMP);
	InjectHook(0x425EA0, &Clock::ForcePauseThroughLua, PATCH_JUMP);
	InjectHook(0x426070, &Clock::SetGameClock, PATCH_JUMP);
	InjectHook(0x425D80, &Clock::IncrementClock, PATCH_JUMP);
	InjectHook(0x425E40, &Clock::GetIsTimeInRange, PATCH_JUMP);
	InjectHook(0x4261A0, &Clock::AdvanceToNightTime, PATCH_JUMP);
	InjectHook(0x425EB0, &Clock::DeterminePauseState, PATCH_JUMP);
	InjectHook(0x4260D0, &Clock::Update, PATCH_JUMP);
}

/*void SetGlobalNormTime(void) { 
	if (gOverrideNormalizedTime) {
		gNormalizedTime = gOverridNormalizedTime;
	}
	else {
		float fhrsInMins = Clock::ms_nGameClockMinutes / 60.0f;
		float fhrsInSecs = Clock::ms_nGameClockSeconds / 3600.0f;
		float fnHours = (Clock::ms_nGameClockHours + fhrsInMins + fhrsInSecs) / 24.0f;
		//TODO: the rest
	}
}*/

void Clock::Initialise(uint32_t scale) {
	ms_nMillisecondsPerGameMinute = scale;
	ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
	ms_nGameClockHours = 12;
	ms_nGameClockMinutes = 0;
	ms_nGameClockSeconds = 0;
	bClockHasBeenStored = false;
	m_bPaused = false;
	m_bForcePauseThroughLua = false;
	ms_nEnableMissionIndex = -1;
	m_bDoTheTimeWarp = false;

	printf("Clock was initialized!\n");
}

bool Clock::GetIsTimeInRange(uint32_t h1, uint32_t h2, uint32_t m1, uint32_t m2) {
	uint32_t curTime = 60 * ms_nGameClockHours + ms_nGameClockMinutes;
	uint32_t t1 = 60 * h1 + m1;
	uint32_t t2 = 60 * h2 + m2;

	return (t1 <= t2) ? curTime >= t1 && curTime < t2 : curTime >= t1 || curTime < t2;
}

bool Clock::IsDayTime(void) {
	return ms_nGameClockHours <= 18;
}

bool Clock::IsNightTime(void) {
	return !IsDayTime();
}

void Clock::StoreClock(void) {
	ms_Stored_nGameClockHours = ms_nGameClockHours;
	ms_Stored_nGameClockMinutes = ms_nGameClockMinutes;
	ms_Stored_nGameClockSeconds = ms_nGameClockSeconds;
	bClockHasBeenStored = true;
}

void Clock::RestoreClock(void) {
	ms_nGameClockHours = ms_Stored_nGameClockHours;
	ms_nGameClockMinutes = ms_Stored_nGameClockMinutes;
	ms_nGameClockSeconds = ms_Stored_nGameClockSeconds;
	SetGlobalNormTime();
}

void Clock::ForcePauseThroughLua(bool bPauseflag) {
	m_bForcePauseThroughLua = bPauseflag;
}

void Clock::IncrementClock(uint32_t m) {
	uint32_t totalMins = ms_nGameClockMinutes + m;
	ms_nGameClockMinutes += m;
	m_bDoTheTimeWarp = m > 5;
	
	if (totalMins >= 60) {
		ms_nGameClockMinutes = totalMins % 60;
		uint32_t totalHours = ms_nGameClockHours + (totalMins - totalMins % 60) / 60;
		ms_nGameClockHours = totalHours;
		if (totalHours >= 24) {
			ms_nGameClockHours = totalHours % 24;
			ms_iDaysPassed += (totalHours - totalHours % 24) / 24;
		}
	}

	SetGlobalNormTime();
}

inline uint32_t Clock::GetGameClockMinutesUntil(uint8_t h, uint8_t m) {
	uint16_t curTime = 60 * ms_nGameClockHours + ms_nGameClockMinutes;
	uint16_t newTime = 60 * h + m;
	if (newTime < curTime)
		newTime += 1440;
	return newTime - curTime;
}

void Clock::SetGameClock(uint8_t h, uint8_t m) {
	ms_nGameClockSeconds = 0;
	ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
	IncrementClock(GetGameClockMinutesUntil(h, m));
}

//static bool (*TimeShouldStop)(void) = (bool(__cdecl *)(void))0x513FE0; //TODO: replace it with the CHud::TimeShouldStop()

void Clock::DeterminePauseState(void) {
	if (!byte_B9DB1C && !dword_C3CD0C && !CCutsceneMgr::ms_running) {
		if (ms_nEnableMissionIndex == -1 || g_MissionMgr->State(ms_nEnableMissionIndex)) {
			if (!m_bForcePauseThroughLua && !CHud::TimeShouldStop() && !sub_425D60(g_Shop)) {
				if (!g_MissionMgr->IsOnMission() || g_MissionMgr->TopInst() < 0) {
					m_bPaused = false;
					return;
				}

				CMissionMgr *pMission = g_MissionMgr->Data(g_MissionMgr->TopInst());
				if (!*(int32_t*)(pMission + 0x2E)) {
					if (*(int32_t*)(pMission + 0x28) == 5) {
						int32_t perIdx = g_ClassSchedule->FindPeriod("PER_TIRED");
						m_bPaused = g_ClassSchedule->IsPeriodActive(perIdx, 0, -1);
					}
					else {
						m_bPaused = false;
					}

					return;
				}
			}
		}
	}

	m_bPaused = true;
}

void Clock::Update(void) {
	DeterminePauseState();
	if (m_bPaused) {
		ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
	}
	else {
		ms_nMillisecondsPerGameMinute = g_MissionMgr->IsOnMission() ?
			ms_nMillisecondsPerGameMinuteOnMission : ms_nMillisecondsPerGameMinuteOffMission;

		uint32_t tMsec = ms_nLastClockTick;

		if (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick > ms_nMillisecondsPerGameMinute) {
			tMsec = CTimer::m_snTimeInMilliseconds;

			uint32_t tMin = (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick) / ms_nMillisecondsPerGameMinute;
			ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
			ms_nGameClockMinutes += tMin;
			m_bDoTheTimeWarp = tMin > 5;

			if (ms_nGameClockMinutes >= 60)
			{
				ms_nGameClockMinutes = 0;
				ms_nGameClockHours++;
				
				if (ms_nGameClockHours >= 24)
				{
					ms_iDaysPassed++;
					ms_nGameClockHours = 0;
				}
			}
		}

		ms_nGameClockSeconds = 60 * (CTimer::m_snTimeInMilliseconds - tMsec) / ms_nMillisecondsPerGameMinute % 60;
	}
}

void Clock::AdvanceToNightTime(void) {
	if (IsDayTime())
		SetGameClock(19, 5);
}