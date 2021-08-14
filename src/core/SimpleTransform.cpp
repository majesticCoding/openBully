#include <math.h>

#include "SimpleTransform.h"

void CSimpleTransform::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x435C20, &CSimpleTransform::Constructor<const CMatrix &>);

	inject_hook(0x46DCA0, &CSimpleTransform::UpdateMatrix);
	inject_hook(0x46D8F0, &CSimpleTransform::UpdateRwMatrix);
	
	inject_hook(0x46D850, &SimpleTransformPoint);
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
		float c = cosf(m_fHeading), s = sinf(m_fHeading);

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

void TransformPoint(CVector& out, CMatrix const& m, CVector const& v) {
	out.x = m.right.x * v.x + m.forward.x * v.y + m.up.x * v.z + m.pos.x;
	out.y = m.right.y * v.x + m.forward.y * v.y + m.up.y * v.z + m.pos.y;
	out.z = m.right.z * v.x + m.forward.z * v.y + m.up.z * v.z + m.pos.z;
}

void SimpleTransformPoint(CVector &out, const CSimpleTransform &a, const CVector &b) {
	out = a.m_vPosn;
	if (a.m_fHeading == 0.f) {
		out += b;
		return;
	}

	float c = cosf(a.m_fHeading), s = sinf(a.m_fHeading);
	out += CVector(
		b.x * c - b.y * s,
		b.x * s + b.y * c,
		b.z
	);
}