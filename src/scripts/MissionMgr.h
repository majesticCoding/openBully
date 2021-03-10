#pragma once
#include "patcher.h"

class CMissionMgr {
public:
	bool		 IsOnMission(void);
	bool		 IsOnClassMission(void);
	bool		 IsOnMinigameMission(void);
	int32_t		 &State(int32_t id);
	int32_t		 &PrimInst(void);
	int32_t		 &SecInst(void);
	int32_t		 &TopInst(void);
	CMissionMgr  *Data(int32_t id);
	void	     Init(const char *, const char *);

	static void InjectHooks(void);
};

extern CMissionMgr *g_MissionMgr;