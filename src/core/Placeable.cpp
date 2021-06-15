#include "Placeable.h"

CPlaceable::CPlaceable(void) {
	XCALL(0x46D9B0);
}

CPlaceable::~CPlaceable() {
	XCALL(0x46DE60);
}

void CPlaceable::InitMatrixArray(void) {
	XCALL(0x46DBF0);
}