#pragma once
#include "patcher.h"
#include "MissionRunInst.h"
#include "Clock.h"

//sizeof(sMissionData) = 0x4C
class CMissionData {
	char _pad[0x4C];
};

//first field is a state: CMissiongMgr::State();
struct sUnkStruct {
	char _pad[0x6];
};

class CMissionMgr {
private:
	char _pad1[1208]; //0
	CMissionData *pMissionData;
	CMissionRunInst primInst; //1212 //sizeof(CMissionRunInst) = 228
	CMissionRunInst secInst; //1440
	char _pad2[4]; //1668
	sUnkStruct *pUnkStr; //1672
	char _pad3[184];
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
	int32_t FindMissionInstSlot(void);
	int32_t &State(int32_t id);
	CMissionRunInst	PrimInst(void);
	CMissionRunInst	SecInst(void);
	CMissionRunInst TopInst(void);
	void GetMissionName(int, char *name, uint32_t);
	CMissionData *Data(int32_t id);
	void MissionStart(int missionId, bool bIsPrimary); //not sure about the 2nd param's name

	virtual ~CMissionMgr();
	virtual void Init(const char *, const char *);
	virtual void Term(void);
	virtual void Update(void);
	virtual int Render(void);
	virtual void Reset(void);

	static void InjectHooks(void);
};

void AdvanceToNextGoodMissionExitTime(void);

extern CMissionMgr &g_MissionMgr;
extern int &missionsMaxNum;