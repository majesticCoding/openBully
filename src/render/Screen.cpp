#include "hook.h"
#include "Screen.h"

void LoadingScreen(char const *str1, char const *str2) {
	printf("%s %s\n", str1, str2); //temporary trick in order to observe what happens via console window
	XCALL(0x43C4F0);
}