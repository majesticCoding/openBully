#include "sndStream.h"

sndStream *g_sndStream = reinterpret_cast<sndStream *>(0xCF4290); //dword_CF4290

void sndStream::SetPosition(CEntity *pEnt, VolumeTableEnum) {
	XCALL(0x5A6D20);
}