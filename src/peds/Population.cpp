#include "hook.h"
#include "Population.h"

CPopulation *CPopulation::m_spInstance = (CPopulation*)(0xC2C108);

void CPopulation::OnChangePeriod(void) {
	XCALL(0x49E7C0);
}

void CPopulation::RemovePedsInSphere(CVector pos, float radius) {
	XCALL(0x49F020);
}