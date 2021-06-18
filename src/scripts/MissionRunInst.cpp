#include "MissionRunInst.h"
#include "UserInputManager.h"
#include "MissionMgr.h"

void CMissionActiveInst::Init(int n_Unk) {

}

void CMissionActiveInst::FinalCleanup(void) {
	if (p_A1 != nullptr) {
		delete p_A1;
		p_A1 = nullptr;
	}

	if (p_A2 != nullptr) {
		delete p_A2;
		p_A2 = nullptr;
	}
}

CMissionRunInst::CMissionRunInst() {
	Init();
}

CMissionRunInst::~CMissionRunInst() {
	; //empty
}

void CMissionRunInst::Init(void) {
	m_missionId = -1;
	m_nUnk1 = 0;
	m_state = 0;

	m_bFlag1 = false;
	m_bFlag2 = false;
	m_bFlag3 = false;
	m_bFlag4 = false;
	m_bFlag5 = false;
	m_bFlag6 = false;
	m_bFlag7 = false;
	m_bFlag8 = false;
	m_bFlag9 = false;
	m_bFlag10 = false;
	m_bFlag11 = false;

	m_secondaryMissionId = -1;

	m_bFlag12 = false;
	m_bFlag13 = false;
	m_bFlag14 = false;

	m_nTexturesCount = 0;
}

int CMissionRunInst::FindTextureForModel(int modelId) {
	if (m_nTexturesCount <= 0)
		return 0;

	//TODO: the rest..
	return 1;
}

bool CMissionRunInst::IsOnMission(void) {
	if (m_missionId == -1)
		return false;

	return GetState() != 0 && GetState() != 1 && GetState() != 11;
}

bool CMissionRunInst::IsMissionRunning(int missionId) {
	if (m_missionId != missionId)
		return false;

	return GetState() != 0 && GetState() != 11;
}

bool CMissionRunInst::IsAnyMissionRunning(void) {
	if (m_missionId == -1)
		return false;

	return GetState() != 0 && GetState() != 11;
}

void CMissionRunInst::RequestCancelForSecondaryMission(int secondaryMissionId) {
	if (IsAnyMissionRunning()) {
		m_secondaryMissionId = secondaryMissionId;
		m_bFlag13 = true;
		m_bFlag11 = true;

		g_UserInputManager->SetInputEnabledFromAreaTransitions(false);
		//InputController::DoBullyDialog(&this->_pad[1], 1, "EXIT_MISSION", "EXIT_BUTTONS", 7, 8);
	}
	else {
		g_MissionMgr.MissionStart(secondaryMissionId, false);
	}
}