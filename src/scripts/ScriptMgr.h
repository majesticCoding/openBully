#pragma once
#include "LuaScript.h"

//TODO: make it as Singleton class with getInstance() and use this method when it's already standalone class
class ScriptManager {
public:
	LuaScript *LoadScript(char const *name, bool flag);
	LuaScript *GetScriptByName(char const *name);
	void UpdateScript(LuaScript *pScript);
};

extern ScriptManager *gScriptManager;