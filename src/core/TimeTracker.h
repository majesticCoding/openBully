#pragma once
#include "common.h"
#include "Timer.h"

class TimeTracker {
	bool m_bIsSet;
	uint32_t m_uInitialTimeInMs;
	uint32_t m_uMilliseconds;
public:
	TimeTracker();

	bool HasFired();
	bool IsRunning();
	void SetSeconds(float seconds);
	void SetMillisecondsOnce(int);
	void SetMilliseconds(int);
	void Clear();
};