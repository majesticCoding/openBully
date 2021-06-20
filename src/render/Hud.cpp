#include "hook.h"
#include "Hud.h"

bool CHud::TimeShouldStop(void) {
	XCALL(0x513FE0);
}