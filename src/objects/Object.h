#pragma once
#include "Physical.h"

class CObject : public CPhysical{
public:
	void operator delete(void* p);
};