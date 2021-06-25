#include <math.h>

#include "SimpleTransform.h"

void CSimpleTransform::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x435C20, &CSimpleTransform::Constructor<const CMatrix &>);

	inject_hook(0x46DCA0, &CSimpleTransform::UpdateMatrix);
	inject_hook(0x46D8F0, &CSimpleTransform::UpdateRwMatrix);
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

void CSimpleTransform::UpdateRwMatrix(RwMatrix *out) {
	if (m_fHeading == 0.f) {
		out->rightx = 1.f;
		out->righty = 0.f;
		out->rightz = 0.f;

		out->forwardx = 0.f;
		out->forwardy = 1.f;
		out->forwardz = 0.f;
	} else {
		float c = cos(m_fHeading), s = sin(m_fHeading);

		out->rightx = c;
		out->righty = s;
		out->rightz = 0.f;

		out->forwardx = -s;
		out->forwardy = c;
		out->forwardz = 0.f;
	}

	out->upx = 0.f;
	out->upy = 0.f;
	out->upz = 1.f;

	out->pos = m_vPosn;
}