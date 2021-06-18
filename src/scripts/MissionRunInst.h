#pragma once
#include "patcher.h"
#include "ActionController.h"
#include "ActionTree.h"

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
};

//sizeof(CMissionRunInst) has to be 228
//TODO: pay attention to _pad* bytes
class CMissionRunInst {
public:
	int m_missionId;
	int m_nUnk1;
	int m_state;
	bool m_bFlag1;
	bool m_bFlag2;
	bool m_bFlag3;
	bool m_bFlag4;
	bool m_bFlag5;
	bool m_bFlag6;
	bool m_bFlag7;
	bool m_bFlag8;
	bool m_bFlag9;
	bool m_bFlag10;
	bool m_bFlag11; //sets true while cancelling
	int m_secondaryMissionId; //not sure
	bool m_bFlag12; 
	bool m_bFlag13; //sets true while cancelling
	bool m_bFlag14;
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
	int GetState() { return m_state; }
	int GetMissionId() { return m_missionId; }  //custom
	int FindTextureForModel(int modelId);
	bool IsMissionRunning(int missionId);
	bool IsAnyMissionRunning(void);
	bool IsOnMission(void);
	void RequestCancelForSecondaryMission(int secondaryMissionId);
};