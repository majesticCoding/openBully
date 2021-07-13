#pragma once
#include <cstdint>

class ActionNode {

};

class ActionTreeName {
	union {
		struct {
			char const *name;
		};

		struct {
			int hash_name;
		};
	};
public:
	ActionTreeName(void);
	ActionTreeName(int32_t);
	ActionTreeName(ActionTreeName const &);
	ActionTreeName(char const *);
	
	~ActionTreeName();
};

class ActionTreeNamePath {
	char _pad[0x8];
public:
	ActionTreeNamePath(int32_t n, ActionTreeName *name);
};