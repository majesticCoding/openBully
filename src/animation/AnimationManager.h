#pragma once
#include "Model.h"
#include "Hierarchy.h"

class RV_AnimationManager {
public:
	static RV_AnimationManager &gAnimationManager;

	void CheckModel(AM_Model *pModel);
	void AddRefToAnimGroup(AM_Hierarchy *pHier, uint32_t u);
	void RemoveRefFromAnimGroup(AM_Hierarchy *pHier, uint32_t u, int32_t i);
};
