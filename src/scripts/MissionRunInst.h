#pragma once
#include "patcher.h"
#include "ActionController.h"
#include "ActionTree.h"

enum eMissionRunInstStates {
	STATE_INACTIVE = 0,
	STATE_RUNNING = 4,
	STATE_FADE_FINISHED = 6,
	STATE_RESTART = 7,
	STATE_FADING,
	STATE_FAILED = 12,
};

class CMissionActiveInst {
public:
	ActionController *p_A1;
	ActionController *p_A2;
	int field_0x8; 

	CMissionActiveInst(void) {
		p_A1 = nullptr;
		p_A2 = nullptr;
		field_0x8 = -1;
	}

	~CMissionActiveInst() {
		if (p_A1 != nullptr)
			delete p_A1;

		if (p_A2 != nullptr)
			delete p_A2;
	}

	void Init(int n_Unk);
	void FinalCleanup(void);
	void RunNode(char const *strStatus);
};

//sizeof(CMissionRunInst) has to be 228
//TODO: pay attention to _pad* bytes
class CMissionRunInst {
public:
	int m_missionId;
	CMissionActiveInst *m_pActiveInstNode;
	eMissionRunInstStates m_state;
	bool m_bSucceed;
	bool m_bRestart;
	bool m_bFlag3;
	bool m_bFailedBusted;
	bool m_bFlag5;
	bool m_bFlag6;
	bool m_bFlag7;
	bool m_bFlag8;
	bool m_bFlag9;
	bool m_bFlag10;
	bool m_bFlag11; //sets true while requesting cancellation
	int m_secondaryMissionId; //not sure
	bool m_bCancelled;
	bool m_bCancellationRequested; //sets true while requesting cancellation
	bool m_bIsActive;
	char _pad1[90];
	int m_nTexturesCount;
	int m_nUnk4;
	int m_nUnk5;
	int m_nUnk6; //140
	char _pad2[84];
	int m_nUnk7;

	CMissionRunInst();
	~CMissionRunInst();

	void Init();
	void Update();
	int GetState() { return m_state; }
	int GetMissionId() { return m_missionId; }  //custom
	int FindTextureForModel(int modelId);
	bool IsMissionRunning(int missionId);
	bool IsAnyMissionRunning(void);
	bool IsOnMission(void);
	bool IsFadingMission(void);
	void RequestCancelForSecondaryMission(int secondaryMissionId);
	void CancelForSecondaryMission(int secondaryMissionId);
	void MissionStart(int missionId);
	void MissionFail(bool, bool, bool, bool, bool, char const* , bool);
	void MissionCleanup();
	void AssociateModelIndiciesWithTextures();
};