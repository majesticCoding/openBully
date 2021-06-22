#include "hook.h"
#include "AnimationManager.h"

RV_AnimationManager &RV_AnimationManager::gAnimationManager = *(RV_AnimationManager*)0x20C4910;

void RV_AnimationManager::CheckModel(AM_Model *pModel) {
	XCALL(0x6C1D00);
}

void RV_AnimationManager::AddRefToAnimGroup(AM_Hierarchy *pHier, uint32_t u) {
	XCALL(0x6BD010);
}

void RV_AnimationManager::RemoveRefFromAnimGroup(AM_Hierarchy *pHier, uint32_t u, int32_t i) {
	XCALL(0x6BD030);
}