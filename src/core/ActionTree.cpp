#include "hook.h"
#include "ActionTree.h"

ActionTreeName::ActionTreeName(void) {
	;
}

ActionTreeName::ActionTreeName(int32_t hash) {
	XCALL(0x5FA870);
}

ActionTreeName::ActionTreeName(ActionTreeName const &name) {
	XCALL(0x5FA880);
}

ActionTreeName::ActionTreeName(char const *) {
	;
}

ActionTreeName::~ActionTreeName() {
	; //empty
}

ActionTreeNamePath::ActionTreeNamePath(int32_t n, ActionTreeName *name) {
	XCALL(0x5FA8C0);
}