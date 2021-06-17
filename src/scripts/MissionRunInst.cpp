#include "MissionRunInst.h"

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