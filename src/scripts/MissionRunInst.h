#pragma once
#include "ActionController.h"
#include "ActionTree.h"
#include "Texture2D.h"
#include "InputController.h"

#define NUMTEXTURES 9

enum eMissionRunInstStates {
	STATE_INACTIVE = 0,
	STATE_INIT,
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
	bool m_bUnk0;
	InputController controller;
	bool _pad1_0;
	bool _pad1_1;
	char _pad1_2[8];
	int m_nUnk1;
	bool m_bFlag12;
	int m_nUnk2;
	int m_nUnk3; //140
	int m_txdSlot;
	char _pad2[4];
	Texture2D m_aTextures[NUMTEXTURES];
	char _pad3[4];
	int m_nTexturesCount;

	CMissionRunInst();
	~CMissionRunInst();

	void Init();
	void ResetState();
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
	void MissionEndMain();
	void MissionCleanup();
	void AssociateModelIndiciesWithTextures();
	void RemoveTextures();

	static void InjectHooks();
};

static_assert(sizeof(CMissionRunInst) == 0xE4, "Invalid CMissionRunInst struct");