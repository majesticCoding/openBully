#include "hook.h"
#include "GlobalButes.h"
#include "ClassSchedule.h"

ActionTreeName &GlobalButes::TimeCycle = *(ActionTreeName*)0x1B653AC;
ActionTreeName &GlobalButes::TimePeriods = *(ActionTreeName*)0x1B653B0;
ActionTreeName &GlobalButes::TimePeriodButes = *(ActionTreeName*)0x1B653B4;

//names
ActionTreeName &GlobalName::ObjectButes = *(ActionTreeName*)0x1B65318;
ActionTreeName &GlobalName::Weapons = *(ActionTreeName*)0x1B6531C;
ActionTreeName &GlobalName::Info = *(ActionTreeName*)0x1B65320;
ActionTreeName &GlobalName::Items = *(ActionTreeName*)0x1B65324;
ActionTreeName &GlobalName::OtherPickups = *(ActionTreeName*)0x1B65328;


int32_t GlobalButes::FindGetCount(ActionTreeNamePath const &path) {
	XCALL(0x72B7D0);
}

void *GlobalButes::Find(ActionTreeNamePath const &path, int32_t n, ActionTreeName &name) {
	XCALL(0x72B810);
}

void *GlobalButes::Find(ActionTreeNamePath const &path, ActionTreeName &name) {
	XCALL(0x72AEA0);
}

void GlobalButes::RegisterCB(void(*f)(void *), void *p) {
	XCALL(0x72B870);
}

void GlobalButes::UnRegisterCB(void(*f)(void *), void *p) {
	XCALL(0x72B8B0);
}