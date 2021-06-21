#pragma once
#include "hook.h"

class HUDInventory {
public:
	bool DoesItemTextureExist(int txdId);
	bool DoesWeaponTextureExist(int txdId);
};