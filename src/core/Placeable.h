#pragma once
#include "Matrix.h"

class CPlaceable{
protected:
	CMatrix m_matrix;

public:
	virtual ~CPlaceable();

	CPlaceable(void);
	static void InitMatrixArray(void);
};