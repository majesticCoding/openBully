#include "ModelInfo.h"

CBaseModelInfo *(&CModelInfo::ms_modelInfoPtrs)[MODELINFOSIZE]
	= *reinterpret_cast<CBaseModelInfo *(*)[MODELINFOSIZE]>(0xC67738);

int CModelInfo::Butes(int idx) {
	XCALL(0x51B450);
}

CColModel *CModelInfo::GetColModel(const CEntity *pEntity) {
	XCALL(0x51AF50);
}