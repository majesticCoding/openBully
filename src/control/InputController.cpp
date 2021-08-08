#include "InputController.h"
#include "hook.h"

void InputController::DoBullyDialog(int, char *command, char *button, UserInput::Type t1, UserInput::Type t2) {
	XCALL(0x705220);
}