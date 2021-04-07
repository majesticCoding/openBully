#include "AnimationManager.h"

RV_AnimationManager &RV_AnimationManager::gAnimationManager = *(RV_AnimationManager*)0x20C4910;

void RV_AnimationManager::CheckModel(AM_Model *pModel) {
	XCALL(0x6C1D00);
}