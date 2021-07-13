#pragma once
#include "Physical.h"
#include "SFXItem.h"

class CObject : public CPhysical {
public:
	CObject();
	~CObject();

	char gap1C0[68];
	int dword204;
	char byte208;
	
	union {
		struct {
			unsigned char b0x1 : 1;
			unsigned char b0x2 : 1;
			unsigned char b0x4 : 1;
			unsigned char b0x8 : 1;
			unsigned char b0x10 : 1;
			unsigned char b0x20 : 1;
			unsigned char b0x40 : 1;
			unsigned char b0x80 : 1;
		};
		unsigned char m_objFlags;
	};

	char byte20A;
	SFXItemPtr dword20C;
	float float210;
	float float214;
	float float218;
	float float21C;
	short word220;
	int dword224;
	int dword228;

	// virtual methods
	void SetIsStatic(bool bIsStatic);
	void ProcessControl();
	void ProcessShift(bool arg0);
	void Teleport(CVector position);
	void Render();
	void SetupLighting();
	bool IsDestroyed();
	bool IsDamageable();
	float GetHitPoints();
	
	void operator delete(void* p);
};