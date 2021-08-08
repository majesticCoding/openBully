#include "hook.h"
#include "MissionRunInst.h"
#include "UserInputManager.h"
#include "MissionMgr.h"
#include "LuaScript.h"
#include "ScriptMgr.h"
#include "TxdStore.h"
#include "ModelIndices.h"
#include "Allocation.h"

void CMissionActiveInst::Init(int n_Unk) {

}

void CMissionActiveInst::FinalCleanup(void) {
	if (p_A1 != nullptr) {
		operator delete(p_A1);
		p_A1 = nullptr;
	}

	if (p_A2 != nullptr) {
		operator delete(p_A2);
		p_A2 = nullptr;
	}
}

void CMissionRunInst::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x6AA190, &CMissionRunInst::Init);
}

CMissionRunInst::CMissionRunInst() {
	Init();
}

CMissionRunInst::~CMissionRunInst() {
	; //empty
}

void CMissionRunInst::Init(void) {
	m_missionId = -1;
	m_pActiveInstNode = nullptr;
	m_state = eMissionRunInstStates::STATE_INACTIVE;
	m_bSucceed = false;
	m_bRestart = false;
	m_bFlag3 = false;
	m_bFailedBusted = false;
	m_bFlag5 = false;
	m_bFlag6 = false;
	m_bFlag7 = false;
	m_bFlag8 = false;
	m_bFlag9 = false;
	m_bFlag10 = false;
	m_bFlag11 = false;
	m_secondaryMissionId = -1;
	m_bCancelled = false;
	m_bCancellationRequested = false;
	m_bIsActive = false;
	_pad1_0 = false;
	m_bFlag12 = false;
	m_nUnk2 = -1;
	m_nUnk3 = 0;
	m_txdSlot = -1;
	m_nTexturesCount = 0;

	printf("MissionRunInst was initialized!\n");
}

void CMissionRunInst::ResetState(void) {
	m_bRestart = false;
	m_bFlag8 = false;
	m_bFlag10 = false;
	m_bFlag7 = false;
	m_bIsActive = false;
	m_pActiveInstNode = nullptr;
	m_state = eMissionRunInstStates::STATE_INACTIVE;
	m_missionId = -1;
}

void CMissionRunInst::Update(void) {
	;
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

	return GetState() != eMissionRunInstStates::STATE_INACTIVE && GetState() != eMissionRunInstStates::STATE_INIT && GetState() != 11;
}

bool CMissionRunInst::IsMissionRunning(int missionId) {
	if (m_missionId != missionId)
		return false;

	return GetState() != eMissionRunInstStates::STATE_INACTIVE && GetState() != 11;
}

bool CMissionRunInst::IsAnyMissionRunning(void) {
	if (m_missionId == -1)
		return false;

	return GetState() != eMissionRunInstStates::STATE_INACTIVE && GetState() != 11;
}

bool CMissionRunInst::IsFadingMission(void) {
	if (m_missionId == -1)
		return false;

	return GetState() != eMissionRunInstStates::STATE_INACTIVE || GetState() == eMissionRunInstStates::STATE_FADING;
}

void CMissionRunInst::RequestCancelForSecondaryMission(int secondaryMissionId) {
	if (IsAnyMissionRunning()) {
		m_secondaryMissionId = secondaryMissionId;
		m_bCancellationRequested = true;
		m_bFlag11 = true;

		g_UserInputManager->SetInputEnabledFromAreaTransitions(false);
		controller.DoBullyDialog(1, "EXIT_MISSION", "EXIT_BUTTONS", UserInput::Type::TYPE_7, UserInput::Type::TYPE_8);
	}
	else {
		g_MissionMgr.MissionStart(secondaryMissionId, false);
	}
}

void CMissionRunInst::CancelForSecondaryMission(int secondaryMissionId) {
	m_secondaryMissionId = secondaryMissionId;
	m_bCancellationRequested = false;
	m_bCancelled = true;

	MissionFail(false, false, false, true, false, nullptr, false);
}

void CMissionRunInst::MissionFail(bool bParam1, bool bParam2, bool bParam3, bool bIsSeconday, bool bParam5, 
	char const *str, bool bParam6) {
	
	;
}

void CMissionRunInst::MissionStart(int missionId) {
	if (missionId < 0 || missionId >= missionsMaxNum || m_pActiveInstNode != nullptr)
		return;

	int missionInstSlot = g_MissionMgr.FindMissionInstSlot();
	if (missionInstSlot == -1)
		return;

	char missionName[64];
	g_MissionMgr.GetMissionName(missionId, missionName, 64);
	m_missionId = missionId;

	//TODO: the rest
}

void CMissionRunInst::MissionCleanup() {
	if (m_pActiveInstNode == nullptr)
		return;

	//TODO: the rest
}

void CMissionRunInst::MissionEndMain() {
	int missionId = GetMissionId();
	if (missionId < 0)
		return;

	LuaScript *pScript = gScriptManager->GetScriptByName(g_MissionMgr.Data(missionId).getMissionName());

	if (pScript != nullptr) {
		pScript->bField_1150 = false;
		pScript->Terminate(false);
	}
}

void CMissionRunInst::AssociateModelIndiciesWithTextures() {
	if (m_txdSlot < 0)
		return;

	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(m_txdSlot);

	for (int i = MI_FIRSTOBJECT; i <= MI_LASTOBJECT; i++) {
		//TODO: the rest
		//[!] HUDInventory and CModelInfo has vmts
	}

	for (int i = MI_FIRSTWEAPON; i <= MI_LASTWEAPON; i++) {
		//TODO: the rest
	}

	CTxdStore::PopCurrentTxd();
}

void CMissionRunInst::RemoveTextures() {
	for (int i = 0; i < m_nTexturesCount; i++)
		RwTextureDestroy(&m_aTextures[i]);
}