#pragma once
#include <cstdint>

class LuaScript {
public:
	int32_t ExecuteFunctionCall(char const *name, uint32_t param2, bool flag);
};