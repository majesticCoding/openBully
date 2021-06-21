#include "hook.h"
#include "BaseModelInfo.h"

CBaseModelInfo::CBaseModelInfo(ModelInfoType type) {
	XCALL(0x50E8C0);
}

void CBaseModelInfo::SetColModel(CColModel *pCol, bool owns) {
	XCALL(0x50EB30);
}