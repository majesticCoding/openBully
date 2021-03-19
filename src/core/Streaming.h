#pragma once
#include "patcher.h"

class CStreaming {
public:
	static void SetModelIsDeletable(int32_t modelId);
	static void DeleteAllRwObjects(void);
	static void RemoveUnusedModelsInLoadedList(void);
};