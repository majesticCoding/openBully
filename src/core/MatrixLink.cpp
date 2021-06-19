#include "MatrixLink.h"

void CMatrixLink::InjectHooks() {
	InjectHook(0x46D770, &CMatrixLink::Constructor, PATCH_JUMP);
}

CMatrixLink *CMatrixLink::Constructor() {
	this->CMatrixLink::CMatrixLink();
	return this;
}

CMatrixLink::CMatrixLink() {
	m_pAttachMatrix = nullptr;
}