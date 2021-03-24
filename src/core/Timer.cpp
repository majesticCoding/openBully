#include "Timer.h"

uint32_t &CTimer::m_snTimeInMilliseconds = *(uint32_t*)0xC1A9B4;

void CTimer::Stop() {
	XCALL(0x45B800);
}