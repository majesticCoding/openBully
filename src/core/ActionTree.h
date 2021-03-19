#pragma once
#include "patcher.h"

class ActionNode {

};

class ActionTreeName {
public:
	ActionTreeName(void);
	ActionTreeName(int32_t);
	ActionTreeName(ActionTreeName const &);
	ActionTreeName(char const *);
	
	~ActionTreeName();
};

class ActionTreeNamePath {
public:
	ActionTreeNamePath(int32_t n, ActionTreeName *name);
};