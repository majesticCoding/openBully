#include "hook.h"
#include "DatManager.h"

DATManager &g_DATManager = *reinterpret_cast<DATManager *>(0x20C7C48);

void DATManager::Init(void) {
	XCALL(0x6D3EA0);
}