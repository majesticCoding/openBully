#pragma once
#include "ActionTree.h"

class GlobalButes {
public:
	static ActionTreeName &TimeCycle;
	static ActionTreeName &TimePeriods;
	static ActionTreeName &TimePeriodButes;

	static int32_t FindGetCount(ActionTreeNamePath const &path);
	static void *Find(ActionTreeNamePath const &path, int32_t n, ActionTreeName &name);
	static void	RegisterCB(void (*f)(void *), void *p);
	static void	UnRegisterCB(void(*f)(void *), void *p);
};