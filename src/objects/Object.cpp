#include "hook.h"
#include "Object.h"

void CObject::operator delete(void *p) { 
	XCALL(0x4D0690);
}