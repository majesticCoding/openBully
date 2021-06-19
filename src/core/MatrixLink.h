#pragma once
#include "Matrix.h"

class CPlaceable;

class CMatrixLink : public CMatrix {
	CMatrixLink *Constructor();
public:
	CPlaceable *m_bOwner;
	CMatrixLink *m_pPrev;
	CMatrixLink *m_pNext;

	CMatrixLink();
	
	static void InjectHooks();
};