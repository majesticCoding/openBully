#pragma once
#include "MissionRunInst.h"
#include "Clock.h"

#define MISSIONS_NUM 498

enum eMissionTypes {
	TYPE_CLASSMISSION = 1,
	TYPE_MINIGAME = 5
};

class CMissionData {
	char _pad1[0x1C];
	char const *missionName;
	char _pad2[0x8];
	eMissionTypes m_missionType;
	char _pad3[0x1D];
public:
	bool bTexturesAreEmpty;
	bool bGotAnAchievement;

	eMissionTypes GetType(void) {
		return m_missionType;
	}

	char const* getMissionName() {
		return missionName;
	}
};
static_assert(sizeof(CMissionData) == 0x4C, "Invalid CMissionData struct");

struct sMissionDatas{
	CMissionData aMissionData[MISSIONS_NUM];
};

struct CMissionState {
	int16_t m_field0;
	int16_t m_field2;
	bool m_bFlag;
};
static_assert(sizeof(CMissionState) == 6, "Invalid CMissionState struct");

class CMissionMgr {
private:
	char _pad1[16]; //4
	CMissionActiveInst m_aInstances[99];
	sMissionDatas *pMissionDatas;
	CMissionRunInst primInst; //1212 //sizeof(CMissionRunInst) = 228
	CMissionRunInst secInst; //1440
	char _pad2[4]; //1668
	CMissionState *pMissionState; //1672
	char _pad3[184];
	int32_t m_nMissionsNum; //1860
	int32_t m_nSuccesCount; //1864
public:
	CMissionMgr();

	bool IsMissionRunning(void);
	bool IsMissionRunning(int missionId);
	bool IsOnGirlMission(void);
	bool IsOnClassMission(void);
	bool IsOnMinigameMission(void);
	bool FadeFinished(void);
	int32_t GetMissionsNum(void);
	int32_t FindMissionInstSlot(void);
	CMissionState State(int32_t id);
	CMissionRunInst	PrimInst(void);
	CMissionRunInst	SecInst(void);
	CMissionRunInst TopInst(void);
	void GetMissionName(int, char *name, uint32_t);
	CMissionData Data(int32_t id);
	void MissionStart(int missionId, bool bIsPrimary); //not sure about the 2nd param's name
	void StopAllThreads(void);
	void StopMission(CMissionRunInst &inst);
	void StopAllMissions(void);
	void SetFadeOut(void);

	static bool IsOnMission(void);

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