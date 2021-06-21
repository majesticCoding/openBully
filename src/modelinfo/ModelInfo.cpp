#include "ModelInfo.h"
#include "hook.h"

CBaseModelInfo **CModelInfo::ms_modelInfoPtrs = reinterpret_cast<CBaseModelInfo **>(0xC67738); //MODELINFOSIZE

int CModelInfo::Butes(int idx) {
	XCALL(0x51B450);
}