#include "hook.h"
#include "References.h"

CReference *&CReferences::pEmptyList = memory::read<CReference *>(0xC11D40);

void CReferences::Init() {
	XCALL(0x450850);
}