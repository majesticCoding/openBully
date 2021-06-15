#pragma once
#include "patcher.h"

class CMissionMgr {
public:
	CMissionMgr() {
		XCALL(0x6AC520);
	}

	bool IsOnMission(void);
	bool IsOnClassMission(void);
	bool IsOnMinigameMission(void);
	int32_t &State(int32_t id);
	int32_t	&PrimInst(void);
	int32_t	&SecInst(void);
	int32_t &TopInst(void);
	CMissionMgr *Data(int32_t id);

	virtual ~CMissionMgr();
	virtual void Init(const char *, const char *);
	virtual void Term(void);
	virtual void Update(void);
	virtual int Render(void);
	virtual void Reset(void);

	static void InjectHooks(void);
};

extern CMissionMgr &g_MissionMgr;