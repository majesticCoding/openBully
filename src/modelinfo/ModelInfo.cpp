#include "ModelInfo.h"

CBaseModelInfo **CModelInfo::ms_modelInfoPtrs = reinterpret_cast<CBaseModelInfo **>(0xC67738); //MODELINFOSIZE

int CModelInfo::Butes(int idx) {
	XCALL(0x51B450);
}

CColModel *CModelInfo::GetColModel(const CEntity *pEntity) {
	XCALL(0x51AF50);
}