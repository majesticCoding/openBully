#include "hook.h"
#include "Area.h"

void CAreaPopulationInfo::Init(void) {
	XCALL(0x4A1100);
}

void CAreaAmbientVehicleInfo::Init(void) {
	XCALL(0x4A83C0);
}