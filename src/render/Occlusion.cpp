#include "hook.h"
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
	using namespace memory::hook;

	inject_hook(0x51CE00, &COcclusion::Init);
	inject_hook(0x51CE50, &COcclusion::AddOne);
	inject_hook(0x51CFC0, &COcclusion::OccluderHidesBehind);
	inject_hook(0x51CF90, &IsPointInsideLine);
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
		aOccluders[prevFreeList].angle = static_cast<int16_t>(angle / 360.0f * UINT16_MAX);
		aOccluders[prevFreeList].ch = ch;
		aOccluders[prevFreeList].listIndex = FarAwayList;
		NumOccludersOnMap++;
		FarAwayList = prevFreeList;
	}
}

bool COcclusion::OccluderHidesBehind(CActiveOccluder *occl1, CActiveOccluder *occl2) {
	for (int i = 0; i < occl1->linesCount; i++) {
		for (int j = 0; j < occl2->linesCount; j++) {
			if (!IsPointInsideLine(occl2->lines[j].origin.x, occl2->lines[j].origin.y, occl2->lines[j].direction.x,
				occl2->lines[j].direction.y, occl1->lines[i].origin.x, occl1->lines[i].origin.y, 0.0f))
				return false;


			if (!IsPointInsideLine(occl2->lines[j].origin.x, occl2->lines[j].origin.y, occl2->lines[j].direction.x,
				occl2->lines[j].direction.y, (occl1->lines[i].origin.x + occl1->lines[i].direction.x * occl1->lines[i].length),
				(occl1->lines[i].origin.y + occl1->lines[i].direction.y * occl1->lines[i].length), 0.0f))
				return false;
		}
	}

	return true;
}

bool IsPointInsideLine(float lineX, float lineY, float lineDX, float lineDY, float pX, float pY, float area = 0.0f) {
	return (pX - lineX) * lineDY - (pY - lineY) * lineDX >= area;
}