#pragma once
#include "hook.h"

#include "MatrixLink.h"
#include "SimpleTransform.h"

class CPlaceable {
	HOOKED_CONSTRUCTOR_CLASS(CPlaceable);
protected:
	CSimpleTransform m_placement;
	CMatrixLink *m_matrix;

public:
	CPlaceable();
	virtual ~CPlaceable();

	void AllocateMatrix();
	void AllocateStaticMatrix();

	CMatrixLink *GetMatrix();
	CMatrix *GetTransform();

	bool IsWithinArea(float x1, float y1, float x2, float y2);
	bool IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2);

	void RemoveMatrix();
	void SetMatrix(const CMatrix &mat, bool bAllocMatrix);

	static void InitMatrixArray();
	static void InjectHooks();
};

extern CMatrix &g_mLastUpdated;