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

class CMissionRunInst {
	int m_missionId;
	char _pad[4];
	int m_state;
public:
	int GetState() {
		return m_state;
	}

	int GetMissionId() { //custom
		return m_missionId;
	}

	bool IsMissionRunning(int missionId);
	bool IsAnyMissionRunning(void);
	bool IsOnMission(void);
};