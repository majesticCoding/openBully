#pragma once
#include "patcher.h"
#include "MissionRunInst.h"

class CMissionMgr {
private:
	char _pad1[1212]; //0
	CMissionRunInst primInst; //1212 //sizeof(CMissionRunInst) = 228
	CMissionRunInst secInst; //1440
	char _pad2[192]; //1668
	int32_t m_nMissionsNum; //1860
	int32_t m_nSuccesCount; //1864
public:
	CMissionMgr() {
		XCALL(0x6AC520);
	}

	bool IsMissionRunning(void);
	bool IsMissionRunning(int missionId);
	bool IsOnMission(void);
	bool IsOnGirlMission(void);
	bool IsOnClassMission(void);
	bool IsOnMinigameMission(void);
	bool FadeFinished(void);
	int32_t GetMissionsNum(void);
	int32_t &State(int32_t id);
	CMissionRunInst	PrimInst(void);
	CMissionRunInst	SecInst(void);
	CMissionRunInst TopInst(void);
	char *GetMissionName(int, char *name, uint32_t);
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