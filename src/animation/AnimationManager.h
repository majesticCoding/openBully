#pragma once
#include "Model.h"

class RV_AnimationManager {
public:
	static RV_AnimationManager &gAnimationManager;

	void CheckModel(AM_Model *pModel);
};
