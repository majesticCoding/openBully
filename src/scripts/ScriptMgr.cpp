#include "hook.h"
#include "ScriptMgr.h"

ScriptManager *gScriptManager = reinterpret_cast<ScriptManager *>(0xD02850);

LuaScript *ScriptManager::LoadScript(char const *name, bool flag) {
	XCALL(0x5DC0F0);
}

LuaScript *ScriptManager::GetScriptByName(char const* name) {
	XCALL(0x5DBCC0);
}

void ScriptManager::UpdateScript(LuaScript *pScript) {
	XCALL(0x5DC0B0);
}