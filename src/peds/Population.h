#pragma once
#include "Vector.h"

class CPopulation {
public:
	static CPopulation *m_spInstance;

	void OnChangePeriod(void);
	void RemovePedsInSphere(CVector pos, float radius);
};