#include "Occlusion.h"

int32_t &COcclusion::NumOccludersOnMap = *(int32_t*)0xC89F8C;
int16_t &COcclusion::FarAwayList = *(int16_t*)0xA76B44;
int16_t &COcclusion::NearbyList = *(int16_t*)0xA76B48;
int16_t &COcclusion::ListWalkThroughFA = *(int16_t*)0xA76B4C;
int16_t &COcclusion::PreviousListWalkThroughFA = *(int16_t*)0xA76B50;
int16_t &COcclusion::FreeList = *(int16_t*)0xA76B54;
COccluder *COcclusion::aOccluders = reinterpret_cast<COccluder *>(0xC8B790);

int16_t &word_C8E8BE = *(int16_t*)0xC8E8BE; //only initialized, never used

void COcclusion::InjectHooks(void) {
	InjectHook(0x51CE00, &COcclusion::Init, PATCH_JUMP);
	InjectHook(0x51CE50, &COcclusion::AddOne, PATCH_JUMP);
}

void COcclusion::Init() {
	NumOccludersOnMap = 0;
	FarAwayList = -1;
	NearbyList = -1;
	ListWalkThroughFA = -1;
	PreviousListWalkThroughFA = -1;
	FreeList = 0;

	for (int32_t idx = 0; idx < NUMOCCLUSIONVOLUMES; idx++)
		aOccluders[idx].listIndex = idx + 1;

	word_C8E8BE = -1;

	printf("COcclusion was initialized!\n");
}

void COcclusion::AddOne(float x, float y, float z, float width, float length, float height, float angle, VisibleAreaEnum area, uint8_t ch) {
	if (NumOccludersOnMap >= NUMOCCLUSIONVOLUMES)
		return;
	
	int16_t prevFreeList;
	if (FreeList != -1) {
		prevFreeList = FreeList;
		FreeList = aOccluders[prevFreeList].listIndex;

		aOccluders[prevFreeList].x = x;
		aOccluders[prevFreeList].y = y;
		aOccluders[prevFreeList].z = z;
		aOccluders[prevFreeList].width = width;
		aOccluders[prevFreeList].length = length;
		aOccluders[prevFreeList].height = height;
		while (angle < 0.0f) angle += 360.0f;
		while (angle > 360.0f) angle -= 360.0f;
		aOccluders[prevFreeList].angle = angle / 360.0f * UINT16_MAX;
		aOccluders[prevFreeList].listIndex = FarAwayList;
		NumOccludersOnMap++;
		FarAwayList = prevFreeList;
	}
}