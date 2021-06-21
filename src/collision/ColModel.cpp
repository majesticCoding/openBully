#include "hook.h"
#include "ColModel.h"

CColModel::~CColModel() {
	XCALL(0x56E7D0);
}

void CColModel::operator delete(void *p) {
	XCALL(0x56EB30);
}