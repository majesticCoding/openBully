#pragma once
#include "Reference.h"

class CReferences {
public:
	static CReference *&pEmptyList;

	static void Init(void);
};