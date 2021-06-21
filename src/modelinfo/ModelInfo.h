#pragma once
#include "BaseModelInfo.h"

#define MODELINFOSIZE 10082

class CModelInfo {
private:
	static CBaseModelInfo **ms_modelInfoPtrs; //MODELINFOSIZE

public:
	//custom method
	static CBaseModelInfo *GetModelInfo(int32_t modelId) {
		return ms_modelInfoPtrs[modelId];
	}
};