#include "hook.h"
#include "ActionTree.h"

ActionTreeName::ActionTreeName(void) {
	;
}

ActionTreeName::ActionTreeName(int32_t) {
	;
}

ActionTreeName::ActionTreeName(ActionTreeName const &name) {
	XCALL(0x5FA880);
}

ActionTreeName::ActionTreeName(char const *) {
	;
}

ActionTreeName::~ActionTreeName() {
	;
}

ActionTreeNamePath::ActionTreeNamePath(int32_t n, ActionTreeName *name) {
	XCALL(0x5FA8C0);
}