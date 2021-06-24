#include "Entity.h"
#include "ModelInfo.h"
#include "References.h"

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
	dwordA0 = 0;
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
	dword18 = 0;
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

bool CEntity::HasPreRenderEffects() {
	XCALL(0x465780);
}

void CEntity::DeleteRwObject(void) {
	XCALL(0x4667A0);
}

// virtual methods
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