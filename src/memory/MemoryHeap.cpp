#include "hook.h"
#include "MemoryHeap.h"

void CMemoryHeap::PushMemId(MemIDsTableEnum id) {
	XCALL(0x5EF0A0);
}

void CMemoryHeap::PopMemId(void) {
	XCALL(0x52E710);
}