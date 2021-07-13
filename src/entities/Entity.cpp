#include "Object.h"
#include "Entity.h"
#include "2dEffect.h"
#include "ModelInfo.h"
#include "References.h"
#include "ModelIndices.h"

short &g_FakeRTTI_ID = memory::read<short>(0xBF3830);

void CEntity::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x4656A0, &CEntity::Constructor<>);

	inject_hook(0x450880, &CEntity::RegisterReference);
	// inject_hook(0x4508D0, &CEntity::CleanUpOldReference);
	inject_hook(0x450910, &CEntity::ResolveReferences);
	inject_hook(0x450970, &CEntity::PruneReferences);
	inject_hook(0x465780, &CEntity::HasPreRenderEffects);
	// inject_hook(0x4667A0, &CEntity::DeleteRwObject);
	// inject_hook(0x512790, &CEntity::ProcessLightsForEntity);
	// inject_hook(0x512760, &CEntity::IsBreakableLight);
	// inject_hook(0x465AB0, &CEntity::UpdateRW);

	inject_hook(0x4657E0, &HelperCleanupOldReference);
	inject_hook(0x4657D0, &HelperRegisterReference);
}

void CEntityFlags::Clear() {
	dword0 = 1;
	dword4 = 0;
	dword8 = 0;
	m_bIsStatic = 0;
	dword10 = 0;
	dword14 = 0;
	dword18 = 0;
	dword1C = 0;
	dword20 = 0;
	dword24 = 0;
	dword28 = 0;
	dword2C = 1;
	dword30 = 0;
	dword34 = 0;
	dword38 = 0;
	dword3C = 0;
	dword40 = 0;
	dword44 = 0;
	dword48 = 0;
	dword4C = 0;
	dword50 = 0;
	dword54 = 0;
	dword58 = 0;
	dword5C = 0;
	dword60 = 0;
	dword64 = 0;
	dword68 = 0;
	dword6C = 0;
	dword70 = 0;
	dword74 = 0;
	dword78 = 0;
	dword7C = 0;
	dword80 = 0;
	dword84 = 0;
	dword88 = 0;
	dword8C = 0;
	dword90 = 0;
	dword94 = 0;
	dword98 = 0;
	dword9C = 0;
	m_bHasPreRenderEffects = 0;
	dwordA4 = 0;
	dwordA8 = 0;
	dwordAC = 0;
	m_bIsDestroyed = 0;
	dwordB4 = 0;
	dwordB8 = 0;
	dwordBC = 0;
	dwordC0 = 0;
	dwordC4 = 0;
	dwordC8 = 0;
	dwordCC = 0;
	dwordD0 = 0;
	dwordD4 = 0;
	dwordD8 = 0;
	dwordDC = 1;
	dwordE0 = 0;
	dwordE4 = 0;
	dwordE8 = 0;
}

CEntity::CEntity() : CPlaceable() {
	m_flags.Clear();
	m_nType = eEntityType::ENTITY_TYPE_NOTHING;
	m_nStatus = 4;
	word10A = 0;
	word112 = 0;
	m_nModelIndex = -1;
	m_pRwObject = nullptr;
	byte110 = -1;
	byte111 = 0;
	dword114 = nullptr;
	m_nRandomSeed = static_cast<unsigned short>(rand());
	float11C = 0.f;
	m_pReferences = nullptr;
}

CEntity::~CEntity() {
	if (m_nModelIndex >= 0) {
		CColModel *colmodel = CModelInfo::GetColModel(this);
		if (colmodel && colmodel->m_pEntity == this)
			colmodel->SetEntity(nullptr);
	}
	DeleteRwObject();
	ResolveReferences();
}

void CEntity::RegisterReference(CEntity **ppEntity) {
	CReference *ref = m_pReferences;
	if (ref) {
		while (ref->m_ppEntity != ppEntity) {
			ref = ref->m_pNext;
			if (!ref)
				break;
		}
	}

	CReference *empty = CReferences::pEmptyList;
	if (!empty)
		return;

	CReferences::pEmptyList = CReferences::pEmptyList->m_pNext;
	empty->m_pNext = m_pReferences;
	m_pReferences = empty;
	empty->m_ppEntity = ppEntity;
}

void CEntity::CleanUpOldReference(CEntity **ppEntity) {
	XCALL(0x4508D0);
	/*if (!m_pReferences)
		return;

	CReference *ref = m_pReferences;
	CReference **pref = &m_pReferences;
	while (ref->m_ppEntity != ppEntity) {
		pref = &ref->m_pNext;
		ref = ref->m_pNext;
		if (!ref)
			return;
		*pref = ref->m_pNext;
		ref->m_pNext = CReferences::pEmptyList;
		CReferences::pEmptyList = ref;
	}*/
}

void CEntity::ResolveReferences() {
	CReference *ref = m_pReferences;
	for (; ref; ref = ref->m_pNext) {
		CEntity **entity = ref->m_ppEntity;
		if (*entity == this)
			*entity = nullptr;
	}

	ref = m_pReferences;
	if (!ref)
		return;

	for (; ref->m_pNext; ref = ref->m_pNext);
	ref->m_pNext = CReferences::pEmptyList;
	CReferences::pEmptyList = m_pReferences;
	m_pReferences = nullptr;
}

void CEntity::PruneReferences() {
	CReference *ref = m_pReferences;
	CReference **pref = &m_pReferences;

	while (ref) {
		if (*ref->m_ppEntity == this) {
			pref = &ref->m_pNext;
			ref = ref->m_pNext;
		} else {
			CReference *next = ref->m_pNext;
			*pref = ref->m_pNext;
			ref->m_pNext = CReferences::pEmptyList;
			CReferences::pEmptyList = ref;
			ref = next;
		}
	}
}

bool CEntity::HasPreRenderEffects() {
	if (!m_flags.dwordA8 && !IsMILight(m_nModelIndex)) {
		int model = m_nModelIndex;
		if (model != MI_QUARTER && model != MI_DOLLAR && !static_cast<CObject*>(this)->b0x1)
			return false;
	}
	return true;
}

void CEntity::DeleteRwObject() {
	XCALL(0x4667A0);
}

void CEntity::ProcessLightsForEntity() {
	XCALL(0x512790);
}

bool CEntity::IsBreakableLight() {
	CBaseModelInfo *info = CModelInfo::GetModelInfo(m_nModelIndex);
	for (C2dEffect* effect = info->GetFirst2dEffect(); effect;
		effect = effect->Next()) {
		if (effect->byte38)
			return true;
	}
	return false;
}

void CEntity::AttachToRwObject(RwObject *pObject) {
	XCALL(0x4666F0);
}

void CEntity::DetachFromRwObject() {
	XCALL(0x466740);
}

void CEntity::GetBoundCentre(CVector &vec) {
	XCALL(0x466C70);
}

void CEntity::UpdateRW() {
	XCALL(0x465AB0);
}

// virtual methods
bool CEntity::IsType(short type) {
	return type == GetCEntity();
}

void CEntity::Add() {
	XCALL(0x465EB0);
}

void CEntity::Remove() {
	XCALL(0x4678F0);
}

bool CEntity::IsBike() {
	return false;
}

bool CEntity::IsCar() {
	return false;
}

void CEntity::SetStatus(unsigned char nStatus) {
	m_nStatus = nStatus;
}

void CEntity::SetIsStatic(bool bIsStatic) {
	m_flags.m_bIsStatic = bIsStatic;
}

void CEntity::SetModelIndex(short nModelIndex, bool arg1) {
	if (m_nModelIndex != -1)
		DeleteRwObject();

	m_nModelIndex = nModelIndex;
	if (nModelIndex == -1) {
		m_flags.m_bHasPreRenderEffects = 0;
		return;
	}

	m_flags.m_bHasPreRenderEffects = HasPreRenderEffects();
	CreateRwObject(true, arg1);
}

void CEntity::SetModelIndexNoCreate(short nModelIndex) {
	m_nModelIndex = nModelIndex;
	m_flags.m_bHasPreRenderEffects = HasPreRenderEffects();
}

void CEntity::CreateRwObject(bool arg0, bool arg1) {
	XCALL(0x4662F0);
}

void CEntity::GetBoundRect(CRect *out) {
	XCALL(0x466970);
}

void CEntity::ProcessControl() {}
void CEntity::ProcessShift(bool arg0) {}
void CEntity::Teleport(CVector position) {}

bool CEntity::PlayHitReaction(float a2, float a3, CPed *a4, int a5, CVector *a6, CVector *a7,
		ActionNode *a8, bool a9, const char *a10, bool a11, float a12, float a13, bool a14, bool a15,
		bool a16, int a17, float a18, CollisionType a19) {
	return 0;
}

void *CEntity::GetContext() {
	return nullptr;
}

void CEntity::PreRender() {
	XCALL(0x466CC0);
}

void CEntity::Render() {
	XCALL(0x466D40);
}

void CEntity::UpdateAnim() {
	XCALL(0x467EB0);
}

bool CEntity::CollidePostAnimUpdate() {
	return false;
}

bool CEntity::ShouldUpdateAnim() {
	return !m_flags.dword88 || m_flags.dwordC8;
}

void CEntity::FlagToDestroyWhenNextProcessed() {}

float CEntity::GetHeight() {
	float radius = GetBoundRadius();
	return radius + radius;
}

void CEntity::GetClosestPoint(CVector *out, const CVector &arg0) {
	XCALL(0x467C00);
}

float CEntity::GetWidth() {
	float radius = GetBoundRadius();
	return radius + radius;
}

float CEntity::GetBoundRadius() {
	return CModelInfo::GetColModel(this)->dwordC;
}

bool CEntity::IsDestroyed() {
	return m_flags.m_bIsDestroyed != 0;
}

bool CEntity::IsDamageable() {
	return IsBreakableLight();
}

float CEntity::GetHitPoints() {
	return 10000.f;
}

bool CEntity::HasObstacle() {
	XCALL(0x467E30);
}

// static
short CEntity::GetCEntity() {
	static short s_id = g_FakeRTTI_ID++;
	return s_id;
}

// global functions
void HelperCleanupOldReference(CEntity *pEntity, CEntity **ppEntity) {
	pEntity->CleanUpOldReference(ppEntity);
}

void HelperRegisterReference(CEntity *pEntity, CEntity **ppEntity) {
	pEntity->RegisterReference(ppEntity);
}