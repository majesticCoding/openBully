#pragma once
#include "Entity.h"

enum VolumeTableEnum {
	VOLUME1 = 1
};

class sndStream {
public:
	void SetPosition(CEntity *pEnt, VolumeTableEnum);
};

extern sndStream *g_sndStream; //dword_CF4290