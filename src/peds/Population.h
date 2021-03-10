#pragma once
#include "patcher.h"

class CPopulation {
public:
	static CPopulation *m_spInstance;

	void OnChangePeriod(void);
};