#pragma once
#include "patcher.h"
#include "Vector.h"

class CPopulation {
public:
	static CPopulation *m_spInstance;

	void OnChangePeriod(void);

	static void RemovePedsInSphere(CVector pos, float radius);
};