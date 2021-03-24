#pragma once
#include "patcher.h"

enum MemIDsTableEnum : int32_t {
	CUTS_MEM_ID = 51
};

class CMemoryHeap {
public:
	static void PushMemId(MemIDsTableEnum id);
};