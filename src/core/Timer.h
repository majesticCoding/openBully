#pragma once
#include "patcher.h"

class CTimer {
public:
	static void Stop(void);

	static uint32_t &m_snTimeInMilliseconds;
};