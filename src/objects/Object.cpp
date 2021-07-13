#include "hook.h"
#include "Object.h"
#include "RwLights.h"
#include "CutsceneMgr.h"

CObject::CObject() : CPhysical() {
	dword204 = 0;
	dword20C.item = nullptr;
	float21C = 1.0;
	float214 = 1.0;
	b0x80 = true;
	b0x10 = true;
	float218 = 1.0;
	float210 = 1.0;
	m_nType = eEntityType::ENTITY_TYPE_OBJECT;
	byte20A = 0;
	byte208 = 0;
	word220 = 0;
	byte111 = 1;
	dword20C.Set(nullptr);
	dword228 = 0;
	dword224 = 0;
}

CObject::~CObject() {
	XCALL(0x4CFBA0);
}

// virtual methods
void CObject::SetIsStatic(bool bIsStatic) {
	if (byte20A == 7)
		m_flags.dword94 = bIsStatic;
	else
		m_flags.m_bIsStatic = bIsStatic;
	byte180 = bIsStatic ? 10 : 0;
}

void CObject::ProcessControl() {
	XCALL(0x4CF4A0);
}

void CObject::ProcessShift(bool arg0) {
	XCALL(0x4CF9C0);
}

void CObject::Teleport(CVector position) {
	XCALL(0x4D0B30);
}

void CObject::Render() {
	if (m_flags.dword78 || (CCutsceneMgr::ms_cutsceneProcessing && b0x1))
		return;

	g_rwLights.LightsUpload(3);
	CEntity::Render();
}

void CObject::SetupLighting() {
	if (b0x10)
		g_rwLights.Colored();
	else
		g_rwLights.SetPropsAmbientColors(1.f);
	g_rwLights.SetSkyColors();
}

bool CObject::IsDestroyed() {
	return !m_flags.dword2C && !m_flags.dword4;
}

bool CObject::IsDamageable() {
	XCALL(0x4CF380);
}

float CObject::GetHitPoints() {
	return word220;
}

void CObject::operator delete(void *p) { 
	XCALL(0x4D0690);
}