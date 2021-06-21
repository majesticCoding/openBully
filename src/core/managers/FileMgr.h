#pragma once
#include <cstdint>

class CFileMgr {
public:
	static int32_t OpenFile(char const *name, char const *mode, bool param);
};