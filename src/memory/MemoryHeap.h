#pragma once
#include <cstdint>

enum MemIDsTableEnum : int32_t {
	TEXTURES_MEM_ID = 23,
	DATMANAGER_MEM_ID = 33,
	CUTS_MEM_ID = 51
};

class CMemoryHeap {
public:
	static void PushMemId(MemIDsTableEnum id);
	static void PopMemId(void);
};