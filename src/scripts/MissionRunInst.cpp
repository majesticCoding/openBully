#include "hook.h"
#include "MissionRunInst.h"
#include "UserInputManager.h"
#include "MissionMgr.h"
#include "LuaScript.h"
#include "ScriptMgr.h"
#include "TxdStore.h"
#include "ModelIndices.h"
#include "Allocation.h"
#include "Minigame.h"
#include "ScreamFireAlarm.h"
#include "TextManager.h"
#include "Game.h"
#include "World.h"

//WARNING[!]: 
//Temporary ptr made for tests, will need to be replaced with g_MissionMgr when the relevant class is reversed
CMissionMgr* MissionMgrPtr = reinterpret_cast<CMissionMgr*>(0x20C3CA0);

void CMissionActiveInst::Init(int n_Unk) {

}

void CMissionActiveInst::RunNode(char const* strStatus) {
	XCALL(0x6AB670);
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
	inject_hook(0x6AA300, &CMissionRunInst::MissionFail);
	inject_hook(0x6AC080, &CMissionRunInst::MissionRun);
	inject_hook(0x6ABF40, &CMissionRunInst::MissionSucceed);
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
	m_bFadingFlag = false;
	m_bPassedOutOrDead = false;
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
	m_bFadingFlag = false;
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

	return GetState() != eMissionRunInstStates::STATE_INACTIVE && GetState() != eMissionRunInstStates::STATE_INIT 
		&& GetState() != 11;
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

void CMissionRunInst::MissionSetup(void) {
	if (m_pActiveInstNode == nullptr)
		return;

	char missionName[MAX_MISSIONNAME_SIZE];
	g_MissionMgr.GetMissionName(m_missionId, missionName, MAX_MISSIONNAME_SIZE);
	
	if (g_MissionMgr.Data(m_missionId).GetType() == eMissionTypes::TYPE_MINIGAME) {
		theTextManager->LoadSecondaryMissionText(missionName);
	}
	else {
		theTextManager->LoadMissionText(missionName);
	}

	if (m_txdSlot != -1)
		CTxdStore::RemoveTxdSlot(m_txdSlot);

	if (g_MissionMgr.Data(m_missionId).bTexturesAreEmpty) {
		char textSlotName[MAX_MISSIONNAME_SIZE * 2];
		
		sprintf_s(textSlotName, "TXD/Missions/%s.NFT", missionName);
		m_txdSlot = CTxdStore::AddTxdSlot(textSlotName);
		CTxdStore::LoadTxd(m_txdSlot, textSlotName);
		CTxdStore::AddRef(m_txdSlot);

		if (m_txdSlot != -1)
			AssociateModelIndiciesWithTextures();
	}

	//TODO: the rest
}

void CMissionRunInst::MissionRun(void) {
	if (m_pActiveInstNode == nullptr)
		return;

	if (g_bIsFireAlarmTurnedOn)
		gpScreamer->StopFireAlarm();

	LuaScript *pScript = gScriptManager->LoadScript(MissionMgrPtr->Data(m_missionId).getMissionName(), true);
	pScript->AddThread("main");
	m_pActiveInstNode->RunNode("Run");
}

void CMissionRunInst::MissionFail(bool bParam1, bool bBusted, bool bPassOutOrDead, bool bIsSeconday, bool bIsMinigame, 
	char const *explanation, bool bParam6) 
{
	
	if (m_pActiveInstNode == nullptr)
		return;

	if (!m_bFailedBusted) 
		m_bFailedBusted = bBusted;
	
	if (!m_bPassedOutOrDead) 
		m_bPassedOutOrDead = bPassOutOrDead;

	if (!m_bFlag5)
		m_bFlag5 = bParam6;

	if (m_state == eMissionRunInstStates::STATE_RUNNING) {
		if (bIsMinigame) {
			if (m_bFailedBusted) {
				Minigame::SetCompletion("M_FAIL", false, 0.0f, "M_FAIL_BUSTED", nullptr, 0);
			}
			else if (m_bPassedOutOrDead) {
				if (Clock::ms_nGameClockHours == 1 && Clock::ms_nGameClockMinutes >= 59
					|| Clock::ms_nGameClockHours >= 2 && Clock::ms_nGameClockHours <= 4) 
				{
					Minigame::SetCompletion("M_FAIL", false, 0.0f, "M_FAIL_PASSOUT", nullptr, 0);
				}
				else
				{
					Minigame::SetCompletion("M_FAIL", false, 0.0f, "M_FAIL_DEAD", nullptr, 0);
				}
			}
			else
			{
				Minigame::SetCompletion("M_FAIL", false, 0.0f, explanation, nullptr, 0);
			}
		}

		m_bSucceed = false;
		m_state = eMissionRunInstStates::STATE_FAILED;
		m_bFlag3 = bParam1;

		if (!bIsSeconday)
			m_bFadingFlag = true;
	}
}

void CMissionRunInst::MissionSucceed(bool bParam1, bool bSetFadeOut, bool bParam3) {
	CGame::m_sbRestartMission = false;
	m_bFlag3 = bParam1;

	if (m_pActiveInstNode == nullptr || GetState() != eMissionRunInstStates::STATE_RUNNING)
		return;

	m_bSucceed = true;
	if (bSetFadeOut) {
		MissionMgrPtr->SetFadeOut();
	}
	else {
		m_bFadingFlag = true;
	}

	m_state = eMissionRunInstStates::STATE_FADING;

	if (MissionMgrPtr->Data(m_missionId).bGotAnAchievement)
		CWorld::Player.SetUnlockPlayerUpgrade(ScriptSaveDataEnum::UPGRADE_28, m_missionId);

	LuaScript* pScript = gScriptManager->GetScriptByName(MissionMgrPtr->Data(m_missionId).getMissionName());
	if (pScript != nullptr)
		pScript->RemoveAllThreadsQueued();
}

void CMissionRunInst::MissionStart(int missionId) {
	if (missionId < 0 || missionId >= missionsMaxNum || m_pActiveInstNode != nullptr)
		return;

	int missionInstSlot = g_MissionMgr.FindMissionInstSlot();
	if (missionInstSlot == -1)
		return;

	char missionName[MAX_MISSIONNAME_SIZE];
	g_MissionMgr.GetMissionName(missionId, missionName, MAX_MISSIONNAME_SIZE);
	m_missionId = missionId;

	//TODO: the rest
}

void CMissionRunInst::MissionStartCleanup() {
	LuaScript* pScript = gScriptManager->GetScriptByName(g_MissionMgr.Data(m_missionId).getMissionName());
	pScript->AddThread("MissionCleanup");
	pScript->bMissionCleanUpStarted = true;
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
		pScript->bMissionCleanUpStarted = false;
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