#include "HUDInventory.h"

bool HUDInventory::DoesItemTextureExist(int txdId) {
	XCALL(0x5411B0);
}

bool HUDInventory::DoesWeaponTextureExist(int txdId) {
	XCALL(0x5411E0);
}