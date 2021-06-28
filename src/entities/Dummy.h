#pragma once
#include "Entity.h"
#include "Object.h"
#include "EntryInfo.h"

class CDummy : public CEntity {
public:
	CDummy();
	~CDummy();

	CEntryInfoList dword120;
	int dword124;

	// virtual methods
	void Add() = 0;
	void Remove() = 0;
	void SetupLighting() = 0;
};

class CDummyObject : public CDummy {
public:
	CDummyObject() = default;
	CDummyObject(CObject *pObject);
	~CDummyObject() = default;
};