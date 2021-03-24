#pragma once
#include "patcher.h"

class CFileMgr {
public:
	static int32_t OpenFile(char const *name, char const *mode, bool param);
};