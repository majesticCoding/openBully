#include "hook.h"
#include "RwLights.h"

CRwLights &g_rwLights = memory::read<CRwLights>(0xD140B8);

void CRwLights::Create(RpWorld *pScene) {
	XCALL(0x5EE3F0);
}

void CRwLights::Destroy() {
	XCALL(0x5EE4A0);
}

void CRwLights::Blackout() {
	;
}

void CRwLights::Colored() {
	;
}

void CRwLights::SetPropsAmbientColors(float color) {
	;
}

void CRwLights::SetSkyColors() {
	;
}

void CRwLights::LightsUpload(unsigned int arg0) {
	// arg0 & 4;
}