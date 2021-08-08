#include "hook.h"
#include "LuaScript.h"

int32_t LuaScript::ExecuteFunctionCall(char const *name, uint32_t param2, bool flag) {
	XCALL(0x5D8200);
}

void LuaScript::RemoveAllThreadsQueued(void) {
	XCALL(0x5D9050);
}

void LuaScript::Terminate(bool bState) {
	XCALL(0x5D9E40);
}

bool LuaScript::IsThreadAlive(char const *threadName) {
	XCALL(0x5D8F10);
}

void LuaScript::AddThread(char const* threadName) {
	XCALL(0x5D9E80);
}