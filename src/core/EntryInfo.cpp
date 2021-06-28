#include "hook.h"
#include "EntryInfo.h"

void CEntryInfoList::Flush() {
	XCALL(0x429840);
}