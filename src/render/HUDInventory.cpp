#include "HUDInventory.h"
#include "ModelInfo.h"
#include "ModelIndices.h"
#include "TxdStore.h"

int *HUDInventory::ms_HUDItemTextures = reinterpret_cast<int *>(0xCEFF20);
int *HUDInventory::ms_HUDWeaponTextures = reinterpret_cast<int *>(0xCEFCC8);

void HUDInventory::Initialize() {
	CTxdStore::PushCurrentTxd();
	int txdSlot = CTxdStore::FindTxdSlot("HUDElems", false);
	CTxdStore::SetCurrentTxd(txdSlot);

	for (int i = MI_FIRSTOBJECT; i <= MI_LASTOBJECT; i++)
	{
		char const *str = *(char const **)(CModelInfo::Butes(i) + 0x4C);
		if (str)
			HUDInventory::ms_HUDItemTextures[i] = MadNoRwTextureRead(str, nullptr);
	}

	for (int i = MI_FIRSTWEAPON; i <= MI_LASTWEAPON; i++)
	{
		char const *str = *(char const **)(CModelInfo::Butes(i) + 0x4C);
		if (str)
			HUDInventory::ms_HUDWeaponTextures[i] = MadNoRwTextureRead(str, nullptr);
	}

	CTxdStore::PopCurrentTxd();
}

bool HUDInventory::DoesItemTextureExist(int itemId) {
	if (itemId < MI_FIRSTOBJECT || itemId > MI_LASTOBJECT)
		return false;

	return HUDInventory::ms_HUDItemTextures[itemId - MI_FIRSTOBJECT] != 0;
}

bool HUDInventory::DoesWeaponTextureExist(int itemId) {
	if (itemId < MI_FIRSTWEAPON || itemId > MI_LASTWEAPON)
		return false;

	return HUDInventory::ms_HUDWeaponTextures[itemId - MI_FIRSTWEAPON] != 0;
}