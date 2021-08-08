#pragma once
#include <cstdint>

class LuaScript {
public:
	char _pad[0x1150];
	bool bField_1150;

	int32_t ExecuteFunctionCall(char const *name, uint32_t param2, bool flag);
	void RemoveAllThreadsQueued(void);
	void Terminate(bool bState);
	bool IsThreadAlive(char const *threadName);
	void AddThread(char const *threadName);
};