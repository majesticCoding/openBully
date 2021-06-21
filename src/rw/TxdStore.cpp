#include "hook.h"
#include "TxdStore.h"

void CTxdStore::Create(int slot) {
	XCALL(0x5F28C0);
}

void CTxdStore::AddRef(int slot) {
	XCALL(0x5F1130);
}

void CTxdStore::LoadTxd(int slot, char const *str) {
	XCALL(0x5F2A80);
}

void CTxdStore::PushCurrentTxd(void) {
	XCALL(0x5F0A90);
}

void CTxdStore::PopCurrentTxd(void) {
	XCALL(0x5F0AA0);
}

void CTxdStore::SetCurrentTxd(int slot) {
	XCALL(0x5F1100);
}

int CTxdStore::AddTxdSlot(char const *str) {
	XCALL(0x5F26E0);
}

int CTxdStore::FindTxdSlot(char const *str, bool bParam) {
	XCALL(0x5F22D0);
}

int MadNoRwTextureRead(char const *name, char const *str) {
	XCALL(0x5F1770);
}