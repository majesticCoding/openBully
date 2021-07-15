#include "Allocation.h"
#include "hook.h"

void operator delete(void* p) {
	XCALL(0x5EEAB0);
}