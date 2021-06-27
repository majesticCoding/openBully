#pragma once
#include "ActionTree.h"

//size = 0x38(56) bytes
struct TimePeriodButes {
	int32_t aUnk[6];
	char const *text;
	char const *str1;
	char const *str2;
	int32_t startHour;
	int32_t startMin;
	int32_t endHour;
	int32_t endMin;
	int32_t type;
};

class GlobalButes {
public:
	static ActionTreeName &TimeCycle;
	static ActionTreeName &TimePeriods;
	static ActionTreeName &TimePeriodButes;

	static int32_t FindGetCount(ActionTreeNamePath const &path);
	static void *Find(ActionTreeNamePath const &path, int32_t n, ActionTreeName &name);
	static void *Find(ActionTreeNamePath const &path, ActionTreeName &name);
	static void	RegisterCB(void (*f)(void *), void *p);
	static void	UnRegisterCB(void(*f)(void *), void *p);
};