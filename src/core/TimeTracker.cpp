#include "TimeTracker.h"

TimeTracker::TimeTracker() {
	Clear();
}

void TimeTracker::Clear() {
	m_bIsSet = false;
	m_uInitialTimeInMs = 0;
	m_uMilliseconds = 0;
}

bool TimeTracker::HasFired() {
	if (m_bIsSet)
		return CTimer::GetTimeInMilliseconds() >= m_uInitialTimeInMs + m_uMilliseconds;

	return false;
}

bool TimeTracker::IsRunning() {
	if (m_bIsSet)
		return CTimer::GetTimeInMilliseconds() < m_uInitialTimeInMs + m_uMilliseconds;

	return false;
}

void TimeTracker::SetSeconds(float seconds) {
	SetMilliseconds(static_cast<int>(1000.0f * seconds));
}

void TimeTracker::SetMillisecondsOnce(int milliseconds) {
	if (!m_bIsSet)
		SetMilliseconds(milliseconds);
}

void TimeTracker::SetMilliseconds(int milliseconds) {
	m_bIsSet = true;
	m_uInitialTimeInMs = CTimer::GetTimeInMilliseconds();
	m_uMilliseconds = milliseconds;
}