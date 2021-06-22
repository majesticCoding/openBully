#include "hook.h"
#include "BaseModelInfo.h"
#include "BullyHash.h"
#include "TxdStore.h"
#include "Streaming.h"
#include "AnimationManager.h"

CBaseModelInfo::CBaseModelInfo(ModelInfoType Type) {
	//XCALL(0x50E8C0);
	m_hash = nullptr;
	m_type = Type;
	m_bOwnsColModel = false;
	m_fieldA = -1;
	m_fieldB = -1;
	m_pCol = nullptr;
	m_2dEffectId = -1;
	m_objectId = -1;
	m_wRefCount = 0;
	//_pad[4] = 0;
}

void CBaseModelInfo::SetColModel(CColModel *pCol, bool bOwns) {
	m_pCol = pCol;
	m_bOwnsColModel = bOwns;
}

void CBaseModelInfo::SetModelName(char const *name) {
	m_hash = HashUCstring(name);
	FindBute();
}

void CBaseModelInfo::FindBute() {
	XCALL(0x50EBF0);
}

void CBaseModelInfo::SetTexDictionary(char const *texDictName, bool bParam) {
	int slot = CTxdStore::FindTxdSlot(texDictName, bParam);
	if (slot == -1)
		slot = CTxdStore::AddTxdSlot(texDictName);

	m_txdSlot = slot;
}

void CBaseModelInfo::AddRefToAllAnimFiles(void) {
	uint32_t u;
	AM_Hierarchy *pHier;

	int32_t animIdx = GetAnimFileIndex();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.AddRefToAnimGroup(pHier, u);
	}

	animIdx = GetAnimFile2Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.AddRefToAnimGroup(pHier, u);
	}

	animIdx = GetAnimFile3Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.AddRefToAnimGroup(pHier, u);
	}

	animIdx = GetAnimFile4Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.AddRefToAnimGroup(pHier, u);
	}
}

void CBaseModelInfo::RemoveRefToAllAnimFiles(void) {
	uint32_t u;
	AM_Hierarchy *pHier;

	int32_t animIdx = GetAnimFileIndex();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.RemoveRefFromAnimGroup(pHier, u, NULL);
	}

	animIdx = GetAnimFile2Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.RemoveRefFromAnimGroup(pHier, u, NULL);
	}

	animIdx = GetAnimFile3Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.RemoveRefFromAnimGroup(pHier, u, NULL);
	}

	animIdx = GetAnimFile4Index();
	if (animIdx != -1) {
		pHier = CStreaming::GetHierarchyFromIndex(animIdx, &u);
		RV_AnimationManager::gAnimationManager.RemoveRefFromAnimGroup(pHier, u, NULL);
	}
}

void CBaseModelInfo::AddRef(void) {
	m_wRefCount++;
	CTxdStore::AddRef(m_txdSlot);
	AddRefToAllAnimFiles();
}

void CBaseModelInfo::RemoveRef(void) {
	m_wRefCount--;
	CTxdStore::AddRef(m_txdSlot);
	RemoveRefToAllAnimFiles();
}

void CBaseModelInfo::DeleteCollisionModel(void) {
	if (m_pCol != nullptr && m_bOwnsColModel) {
		delete m_pCol;
		m_pCol = nullptr;
	}
}

void CBaseModelInfo::Delete2dEffects(void) {
	XCALL(0x50EDA0);
}

void CBaseModelInfo::Shutdown(void) {
	DeleteCollisionModel();
	DeleteRwObject();
	Delete2dEffects();

	m_txdSlot = -1;
	m_objectId = -1;
}

bool CBaseModelInfo::IsModelName(char const *name) {
	return m_hash == HashUCstring(name);
}