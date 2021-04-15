#pragma once
#include "patcher.h"

class CColModel {
public:
	~CColModel();

	void operator delete(void* p);
};