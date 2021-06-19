#pragma once
#include "Matrix.h"

class CSimpleTransform {
	CSimpleTransform *Constructor(const CMatrix &mat);
public:
	CSimpleTransform() = default;
	CSimpleTransform(const CMatrix &mat);

	CVector m_vPosn;
	float m_fHeading;

	void UpdateMatrix(CMatrix *out);

	static void InjectHooks();
};