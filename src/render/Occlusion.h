#pragma once
#include "patcher.h"

#define NUMOCCLUSIONVOLUMES 350

enum VisibleAreaEnum : uint32_t {

};

class COccluder {
public:
	float length, width, height;
	float x, y, z;
	int16_t angle;
	int16_t listIndex;
	uint8_t ch;
	char _pad[3];
	VisibleAreaEnum area;
};

class COcclusion {
public:
	static int32_t &NumOccludersOnMap;
	static int16_t &FarAwayList;
	static int16_t &NearbyList;
	static int16_t &ListWalkThroughFA;
	static int16_t &PreviousListWalkThroughFA;
	static int16_t &FreeList;

	static COccluder *aOccluders;

	static void Init(void);
	static void AddOne(float x, float y, float z, float width, float length, float height, float angle, VisibleAreaEnum area, uint8_t ch);

	static void InjectHooks(void);
};