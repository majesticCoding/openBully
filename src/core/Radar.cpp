#include "hook.h"
#include "Radar.h"

void HUDRadar::RemoveRadarSections(void) {
	XCALL(0x5492E0);
}