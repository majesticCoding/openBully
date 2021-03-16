#include "Directory.h"

CDirectoryTemplate<CDirectoryInfo>::CDirectoryTemplate(int32_t n) {
	XCALL(0x4291B0);
}

CDirectoryTemplate<CDirectoryInfo>::~CDirectoryTemplate() {
	XCALL(0x429180);
}

void CDirectoryTemplate<CDirectoryInfo>::ReadDirFile(char const *fileName) {
	XCALL(0x4291F0);
}

bool CDirectoryTemplate<CDirectoryInfo>::FindItem(char const *itemName, uint32_t &, uint32_t &) {
	return true;
}

bool CDirectoryTemplate<CDirectoryInfo>::FindItem(uint32_t itemNum, uint32_t &, uint32_t &) {
	return true;
}

void CDirectoryTemplate<CDirectoryInfo>::FindItem(uint32_t itemNum) {
	XCALL(0x429070);
}

int32_t CDirectoryTemplate<CDirectoryInfo>::GetPositionSize(int32_t, uint32_t &, uint32_t &) {
	XCALL(0x429130);
}

void CDirectoryTemplate<CDirectoryInfo>::SetPositionSize(int32_t, uint32_t, uint32_t) {
	XCALL(0x429160);
}

void CDirectoryTemplate<CDirectoryInfo>::Empty(void) {
	;
}

int32_t CDirectoryTemplate<CDirectoryInfo>::GetNumItems(void) {
	return 1;
}