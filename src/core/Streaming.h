#pragma once
#include <cstdint>
#include "Hierarchy.h"

class CStreaming {
public:
	static bool &ms_disableStreaming;

	static void SetModelIsDeletable(int32_t modelId);
	static void DeleteAllRwObjects(void);
	static void RemoveUnusedModelsInLoadedList(void);
	static void RemoveCurrentZonesModels(void);
	static void SetMissionDoesntRequireSpecialChar(int32_t modelId);
	static void RemoveModel(int32_t modelId);
	static bool RemoveLoadedVehicle(void);
	static void RequestModel(int32_t, int32_t);
	static AM_Hierarchy *CStreaming::GetHierarchyFromIndex(int32_t, uint32_t *);
};