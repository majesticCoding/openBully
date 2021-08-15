#include "ScreamFireAlarm.h"
#include "hook.h"

bool &g_bIsFireAlarmTurnedOn = *(bool*)0xCF3DC0;
ScreamFireAlarm* gpScreamer = reinterpret_cast<ScreamFireAlarm*>(0xCF3DA8);

void ScreamFireAlarm::StopFireAlarm() {
	XCALL(0x5950B0);
}