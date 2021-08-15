#pragma once

class ScreamFireAlarm {
public:
	void StopFireAlarm();
};

extern bool &g_bIsFireAlarmTurnedOn;
extern ScreamFireAlarm *gpScreamer;