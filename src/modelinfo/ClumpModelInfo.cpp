#include "ClumpModelInfo.h"

CClumpModelInfo::~CClumpModelInfo() {
	XCALL(0x510D90);
}

void CClumpModelInfo::DeleteRwObject(void) {
	XCALL(0x510C40);
}