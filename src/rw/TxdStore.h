#pragma once

class CTxdStore {
public:
	static void Create(int);
	static void AddRef(int);
	static void LoadTxd(int, char const *str);
	static void SetCurrentTxd(int slot);
	static void PushCurrentTxd(void);
	static void PopCurrentTxd(void);
	static int AddTxdSlot(char const *str);
	static int FindTxdSlot(char const *str, bool);
};

int MadNoRwTextureRead(char const *name, char const *str);