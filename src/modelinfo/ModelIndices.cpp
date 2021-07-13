#include "hook.h"
#include "ModelIndices.h"

int32_t &MI_FIRSTOBJECT = *(int32_t*)0xA136B8;
int32_t &MI_LASTOBJECT = *(int32_t*)0xA136BC;
int32_t &MI_FIRSTWEAPON = *(int32_t*)0xA136B0;
int32_t &MI_LASTWEAPON = *(int32_t*)0xA136B4;
int32_t &MI_FIRSTSPECIALCHAR = *(int32_t*)0xA136D0;
int32_t &MI_LASTSPECIALCHAR = *(int32_t*)0xA136D4;
int32_t &MI_QUARTER = *(int32_t*)0xBF44EC;
int32_t &MI_DOLLAR = *(int32_t*)0xBF44E8;

bool IsMILight(int model) {
	XCALL(0x43F3A0);
}