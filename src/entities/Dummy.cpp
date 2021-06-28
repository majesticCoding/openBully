#include "Dummy.h"
#include "RwLights.h"

CDummy::CDummy() : CEntity() {
	dword120.m_pNode = nullptr;
	dword124 = 0;
	m_nType = eEntityType::ENTITY_TYPE_DUMMY;
}

CDummy::~CDummy() {
	dword120.Flush();
}

void CDummy::Add() {
	XCALL(0x4651A0);
}

void CDummy::Remove() {
	XCALL(0x4653B0);
}

void CDummy::SetupLighting() {
	g_rwLights.Blackout();
}

CDummyObject::CDummyObject(CObject *pObject) {
	XCALL(0x4CF220);
}