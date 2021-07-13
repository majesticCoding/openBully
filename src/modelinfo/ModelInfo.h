#pragma once
#include "Entity.h"
#include "BaseModelInfo.h"

#define MODELINFOSIZE 12200

class CModelInfo {
private:
	static CBaseModelInfo *(&ms_modelInfoPtrs)[MODELINFOSIZE];

public:
	//custom method
	static CBaseModelInfo *GetModelInfo(int32_t modelId) {
		return ms_modelInfoPtrs[modelId];
	}

	static int Butes(int idx);
	static CColModel *GetColModel(const CEntity *pEntity);
};