#include "hook.h"
#include "MissionMgr.h"
#include "ScriptMgr.h"
#include "CameraManager.h"

CMissionMgr &g_MissionMgr = *reinterpret_cast<CMissionMgr *>(0x20C3CA0);

int &missionsMaxNum = *(int*)0x20C43E4;

void CMissionMgr::InjectHooks(void) {
	//InjectHook(0x6AA680, &CMissionMgr::PrimInst, PATCH_JUMP);
	//InjectHook(0x6AA690, &CMissionMgr::SecInst, PATCH_JUMP);
	//InjectHook(0x6AA840, &CMissionMgr::IsOnClassMission, PATCH_JUMP);
	//InjectHook(0x6AA890, &CMissionMgr::IsOnMinigameMission, PATCH_JUMP);
	//InjectHook(0x6AA7C0, &CMissionMgr::State, PATCH_JUMP);
	//InjectHook(0x6AA660, &CMissionMgr::Data, PATCH_JUMP);
}

CMissionMgr::CMissionMgr() {
	XCALL(0x6AC520);
}

CMissionRunInst CMissionMgr::PrimInst(void) {
	//XCALL(0x6AA680);

	return primInst;
}

CMissionRunInst CMissionMgr::SecInst(void) {
	//XCALL(0x6AA690);

	return secInst;
}

bool CMissionMgr::IsMissionRunning(void) {
	return PrimInst().IsAnyMissionRunning() || SecInst().IsAnyMissionRunning();
}

bool CMissionMgr::IsMissionRunning(int missionId) {
	return PrimInst().IsMissionRunning(missionId) || SecInst().IsMissionRunning(missionId);
}

bool CMissionMgr::IsOnMission(void) {
	XCALL(0x6AA7E0);
}

bool CMissionMgr::IsOnGirlMission(void) {
	char name[132];
	int missionId = PrimInst().GetMissionId();
	
	if (missionId >= 0) {
		GetMissionName(missionId, name, 0x80);
		if (strstr(name, "_G") != nullptr)
			return true;
	}

	missionId = SecInst().GetMissionId();

	if (missionId >= 0) {
		GetMissionName(missionId, name, 0x80);
		if (strstr(name, "_G") != nullptr)
			return true;
	}

	return false;
}

void CMissionMgr::GetMissionName(int missionId, char *name, uint32_t size) {
	if (missionId < 0)
		return;
}

bool CMissionMgr::IsOnClassMission(void) {
	int missionId = PrimInst().GetMissionId();
	if (missionId >= 0 && pMissionDatas->aMissionData[missionId].GetType() == TYPE_CLASSMISSION)
		return true;

	missionId = SecInst().GetMissionId();
	if (missionId >= 0 && pMissionDatas->aMissionData[missionId].GetType() == TYPE_CLASSMISSION)
		return true;

	return false;

	//XCALL(0x6AA840);
}

bool CMissionMgr::IsOnMinigameMission(void) {
	int missionId = PrimInst().GetMissionId();
	if (missionId >= 0 && pMissionDatas->aMissionData[missionId].GetType() == TYPE_MINIGAME)
		return true;

	missionId = SecInst().GetMissionId();
	if (missionId >= 0 && pMissionDatas->aMissionData[missionId].GetType() == TYPE_MINIGAME)
		return true;

	return false;

	//XCALL(0x6AA890);
}

int32_t &CMissionMgr::State(int32_t id) {
	//return *(int32_t*)(*(int32_t*)(&g_MissionMgr + 0x688) + 0x6 * id);
	XCALL(0x6AA7C0);
}

CMissionRunInst CMissionMgr::TopInst(void) { //mission's id
	//XCALL(0x6AA790);

	return PrimInst().IsOnMission() ? PrimInst() : SecInst();
}

CMissionData CMissionMgr::Data(int32_t missionId) {
	//XCALL(0x6AA660);
	
	if (missionId >= 0 && missionId < GetMissionsNum())
		return pMissionDatas->aMissionData[missionId];
	else
		return pMissionDatas->aMissionData[0];
}

int32_t CMissionMgr::GetMissionsNum(void) {
	return m_nMissionsNum;
}

int32_t CMissionMgr::FindMissionInstSlot(void) {
	return 0;
}

bool CMissionMgr::FadeFinished(void) {
	return g_CameraManager->GetScreenFadeStatus() != 2; //TODO: replace with the enum
}

void CMissionMgr::MissionStart(int missionId, bool bIsPrimary) {
	;
}

void CMissionMgr::StopAllThreads(void) {
	int missionId = SecInst().GetMissionId();
	if (missionId >= 0) {
		gScriptManager->GetScriptByName(Data(missionId).getMissionName())->RemoveAllThreadsQueued();
	}

	missionId = PrimInst().GetMissionId();
	if (missionId >= 0) {
		gScriptManager->GetScriptByName(Data(missionId).getMissionName())->RemoveAllThreadsQueued();
	}
}

void CMissionMgr::StopMission(CMissionRunInst &inst) {
	int missionId = inst.GetMissionId();
	if (missionId < 0)
		return;

	inst.MissionFail(false, false, false, false, false, '\0', false);
	inst.MissionEndMain();

	LuaScript *pScript = gScriptManager->GetScriptByName(g_MissionMgr.Data(missionId).getMissionName());

	if (pScript != nullptr) {
		while (pScript->IsThreadAlive("main")) {
			gScriptManager->UpdateScript(pScript);
		}
		
		pScript->AddThread("MissionCleanup");
		pScript->bField_1150 = true;

		while (pScript->IsThreadAlive("MissionCleanup")) {
			gScriptManager->UpdateScript(pScript);
		}
	}

	inst.MissionCleanup();
	inst.ResetState();
}

void CMissionMgr::StopAllMissions() {
	StopAllThreads();
	StopMission(primInst);
	StopMission(secInst);
}

void AdvanceToNextGoodMissionExitTime(void) {
	switch (Clock::ms_nGameClockHours) {
	case 0:
	case 23:
	case 24:
		Clock::SetGameClock(1, 0);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		Clock::SetGameClock(9, 0);
		break;
	case 9:
	case 10:
	case 11:
		if (Clock::ms_nGameClockHours >= 11 && Clock::ms_nGameClockMinutes >= 30)
			Clock::SetGameClock(13, 0);
		else
			Clock::SetGameClock(11, 30);
		break;
	case 12:
		Clock::SetGameClock(13, 0);
		break;
	case 13:
	case 14:
	case 15:
		if (Clock::ms_nGameClockHours >= 15 && Clock::ms_nGameClockMinutes >= 30)
			Clock::SetGameClock(18, 0);
		else
			Clock::SetGameClock(15, 30);
		break;
	case 16:
	case 17:
		Clock::SetGameClock(18, 0);
		break;
	case 18:
	case 19:
	case 20:
		Clock::SetGameClock(21, 0);
		break;
	case 21:
	case 22:
		Clock::SetGameClock(23, 0);
		break;
	default:
		Clock::SetGameClock(23, 0);
		break;
	}
}

/*=================================== VIRTUAL METHODS =======================================*/

CMissionMgr::~CMissionMgr() {
	XCALL(0x6AC710);
}

void CMissionMgr::Init(const char *s1, const char *s2) {
	XCALL(0x6AC730);
}

void CMissionMgr::Term(void) {
	XCALL(0x6AC990);
}

void CMissionMgr::Update(void) {
	XCALL(0x6ADDD0);
}

int CMissionMgr::Render(void) {
	XCALL(0x6ABAC0);
}

void CMissionMgr::Reset(void) {
	XCALL(0x6AB7B0);
}