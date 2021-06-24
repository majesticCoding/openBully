#include "hook.h"
#include "ColModel.h"

CColModel::CColModel() {
	dword0 = 0.f;
	dword4 = 0.f;
	short30 = 0;
	dword8 = 0.f;
	short32 = 0;
	m_pData = nullptr;
	m_pEntity = nullptr;
	byte34 = 0;
}

CColModel::~CColModel() {
	XCALL(0x56E7D0);
}

void CColModel::SetEntity(CEntity *pEntity) {
	XCALL(0x51AF50);
}

void CColModel::operator delete(void *p) {
	XCALL(0x56EB30);
}