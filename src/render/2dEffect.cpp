#include "hook.h"
#include "2dEffect.h"

C2dEffect *C2dEffect::Next() {
	// C2dEffect::Next & CBaseModelInfo::GetFirst2dEffect are identical
	XCALL(0x50ED70);
}