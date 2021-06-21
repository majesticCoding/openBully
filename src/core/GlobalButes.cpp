#include "hook.h"
#include "GlobalButes.h"
#include "ClassSchedule.h"

ActionTreeName &GlobalButes::TimeCycle = *(ActionTreeName*)0x1B653AC;
ActionTreeName &GlobalButes::TimePeriods = *(ActionTreeName*)0x1B653B0;
ActionTreeName &GlobalButes::TimePeriodButes = *(ActionTreeName*)0x1B653B4;


int32_t GlobalButes::FindGetCount(ActionTreeNamePath const &path) {
	XCALL(0x72B7D0);
}

void *GlobalButes::Find(ActionTreeNamePath const &path, int32_t n, ActionTreeName &name) {
	XCALL(0x72B810);
}

void GlobalButes::RegisterCB(void(*f)(void *), void *p) {
	XCALL(0x72B870);
}

void GlobalButes::UnRegisterCB(void(*f)(void *), void *p) {
	XCALL(0x72B8B0);
}