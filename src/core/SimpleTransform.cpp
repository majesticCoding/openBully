#include <math.h>

#include "SimpleTransform.h"

void CSimpleTransform::InjectHooks() {
	InjectHook(0x435C20, &CSimpleTransform::Constructor, PATCH_JUMP);

	InjectHook(0x46DCA0, &CSimpleTransform::UpdateMatrix, PATCH_JUMP);
}

CSimpleTransform *CSimpleTransform::Constructor(const CMatrix &mat) {
	this->CSimpleTransform::CSimpleTransform(mat);
	return this;
}

CSimpleTransform::CSimpleTransform(const CMatrix &mat) {
	m_vPosn = mat.pos;
	m_fHeading = atan2f(-mat.forward.x, mat.forward.y);
}

void CSimpleTransform::UpdateMatrix(CMatrix *out) {
	out->SetRotateZOnly(m_fHeading);
	out->pos = m_vPosn;
	// out->pw = v6;
}