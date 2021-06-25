#include "Entity.h"
#include "ModelInfo.h"
#include "References.h"

short &g_FakeRTTI_ID = memory::read<short>(0xBF3830);

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

CEntity::CEntity() {
	m_flags.Clear();
	m_nType = 1;
	m_nStatus = 0;
	word10A = 0;
	word112 = 0;
	m_nModelIndex = -1;
	m_pRwObject = nullptr;
	byte110 = -1;
	byte111 = 0;
	dword114 = nullptr;
	m_nRandomSeed = rand();
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
	XCALL(0x450880);
}

void CEntity::CleanUpOldReference(CEntity **pEntity) {
	XCALL(0x4508D0);
}

void CEntity::ResolveReferences() {
	XCALL(0x450910);
}

void CEntity::PruneReferences() {
	XCALL(0x450970);
}

char CEntity::HasPreRenderEffects() {
	XCALL(0x465780);
}

void CEntity::DeleteRwObject(void) {
	XCALL(0x4667A0);
}

void CEntity::ProcessLightsForEntity() {
	XCALL(0x512790);
}

char CEntity::IsBreakableLight() {
	XCALL(0x512760);
}

// virtual methods
bool CEntity::IsType(short type) {
	return type == GetCEntity();
}

bool CEntity::IsBike() {
	return false;
}

bool CEntity::IsCar() {
	return false;
}

void CEntity::SetStatus(int nStatus) {
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

void CEntity::ProcessControl() {}
void CEntity::ProcessShift(bool arg0) {}
void CEntity::Teleport(CVector position) {}

char CEntity::PlayHitReaction(float a2, float a3, CPed *a4, int a5, CVector *a6, CVector *a7,
		ActionNode *a8, bool a9, const char *a10, bool a11, float a12, float a13, bool a14, bool a15,
		bool a16, int a17, float a18, CollisionType a19) {
	return 0;
}

void *CEntity::GetContext() {
	return nullptr;
}

bool CEntity::CollidePostAnimUpdate() {
	return false;
}

char CEntity::ShouldUpdateAnim() {
	return !m_flags.dword88 || m_flags.dwordC8;
}

void CEntity::FlagToDestroyWhenNextProcessed() {}

float CEntity::GetHeight() {
	float radius = GetBoundRadius();
	return radius + radius;
}

float CEntity::GetWidth() {
	float radius = GetBoundRadius();
	return radius + radius;
}

float CEntity::GetBoundRadius() {
	return CModelInfo::GetColModel(this)->dwordC;
}

char CEntity::IsDestroyed() {
	return m_flags.m_bIsDestroyed != 0;
}

char CEntity::IsDamageable() {
	return IsBreakableLight();
}

float CEntity::GetHitPoints() {
	return 10000.f;
}

// static
short CEntity::GetCEntity() {
	static short s_id = g_FakeRTTI_ID++;
    return s_id;
}