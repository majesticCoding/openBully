#include "PathManager.h"

PathManager *g_PathManager = reinterpret_cast<PathManager*>(0xD13CB4);

PathManager::PathManager(void) {
	XCALL(0x5ED540);
}