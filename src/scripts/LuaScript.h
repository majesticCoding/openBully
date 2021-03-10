#pragma once
#include "patcher.h"

class LuaScript {
public:
	int32_t ExecuteFunctionCall(char const *name, uint32_t param2, bool flag);
};