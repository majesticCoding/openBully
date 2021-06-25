#pragma once
#include "hook.h"
#include "Matrix.h"

class CSimpleTransform {
	HOOKED_CONSTRUCTOR_CLASS(CSimpleTransform)
public:
	CSimpleTransform() = default;
	CSimpleTransform(const CMatrix &mat);

	CVector m_vPosn;
	float m_fHeading;

	void UpdateMatrix(CMatrix *out);
	void UpdateRwMatrix(RwMatrix *out);

	static void InjectHooks();
};