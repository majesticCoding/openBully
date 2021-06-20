#pragma once

class CTxdStore {
public:
	static void Create(int);
	static void AddRef(int);
	static void LoadTxd(int, char const *str);
	static void SetCurrentTxd(int slot);
	static int AddTxdSlot(char const *str);
};