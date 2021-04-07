#pragma once
#include "patcher.h"
#include "ClumpModelInfo.h"

class CPedModelInfo : public CClumpModelInfo {
public:
	void SetModelName(char const *name, int32_t n);
};