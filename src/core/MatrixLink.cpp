#include "hook.h"
#include "MatrixLink.h"

void CMatrixLink::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x46D770, &CMatrixLink::Constructor);
}

CMatrixLink *CMatrixLink::Constructor() {
	this->CMatrixLink::CMatrixLink();
	return this;
}

CMatrixLink::CMatrixLink() {
	m_pAttachMatrix = nullptr;
}