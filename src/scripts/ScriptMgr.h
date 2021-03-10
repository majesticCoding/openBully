#pragma once
#include "patcher.h"
#include "LuaScript.h"

class ScriptManager {
public:
	LuaScript *LoadScript(char const *name, bool flag);
	void	  UpdateScript(LuaScript *pScript);
};

extern ScriptManager *gScriptManager;
