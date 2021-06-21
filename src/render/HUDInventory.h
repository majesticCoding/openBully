#pragma once
#include "hook.h"

#define HUDITEMTEXTURES 80
#define HUDWEAPONTEXTURES 150

class HUDComponent {
public:

};

class HUDInventory : public HUDComponent {
public:
	static int *ms_HUDItemTextures;
	static int *ms_HUDWeaponTextures;

	void Initialize(void);
	bool DoesItemTextureExist(int itemId);
	bool DoesWeaponTextureExist(int itemId);

	virtual ~HUDInventory() {
		XCALL(0x5412F0);
	}
	virtual void _fB4() = 0;
	virtual void _fB8() = 0;
	/*
	virtual bool HUDComponent::IsType(int8_t);
	virtual bool HUDComponent::GetVisibility();
	virtual void HUDComponent::SetVisibility(bool bVisible);
	*/
	virtual void _fC8();
	virtual void Reset();
	virtual void Draw();
	virtual void _fDC() = 0;
	virtual void _fE0() = 0;
};