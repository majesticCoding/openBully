#include "MissionMgr.h"

CMissionMgr &g_MissionMgr = *reinterpret_cast<CMissionMgr *>(0x20C3CA0);

void CMissionMgr::InjectHooks(void) {
	//InjectHook(0x6AA680, &CMissionMgr::PrimInst, PATCH_JUMP);
	//InjectHook(0x6AA690, &CMissionMgr::SecInst, PATCH_JUMP);
	//InjectHook(0x6AA840, &CMissionMgr::IsOnClassMission, PATCH_JUMP);
	//InjectHook(0x6AA890, &CMissionMgr::IsOnMinigameMission, PATCH_JUMP);
	//InjectHook(0x6AA7C0, &CMissionMgr::State, PATCH_JUMP);
	//InjectHook(0x6AA660, &CMissionMgr::Data, PATCH_JUMP);
}

int32_t &CMissionMgr::PrimInst(void) {
	XCALL(0x6AA680);
	return *(int32_t*)(&g_MissionMgr + 0x4BC);
}

int32_t &CMissionMgr::SecInst(void) {
	XCALL(0x6AA690);
	//return *(int32_t*)(&g_MissionMgr + 0x5A0);
}

bool CMissionMgr::IsOnMission(void) {
	XCALL(0x6AA7E0);
}

bool CMissionMgr::IsOnClassMission(void) {
	/*int32_t pInst = (&g_MissionMgr)->PrimInst();
	if (pInst >= 0 && *(int32_t*)(g_MissionMgr.Data(pInst) + 0x28) == 1)
		return true;

	int32_t sInst = (&g_MissionMgr)->SecInst();
	if (sInst < 0)
		return false;
	else 
		return *(int32_t*)(g_MissionMgr.Data(sInst) + 0x28) == 1;*/

	XCALL(0x6AA840);
}

bool CMissionMgr::IsOnMinigameMission(void) {
	/*int32_t pInst = g_MissionMgr.PrimInst();
	if (pInst >= 0 && *(int32_t*)(g_MissionMgr.Data(pInst) + 0x28) == 5)
		return true;

	int32_t sInst = (&g_MissionMgr)->SecInst();
	if (sInst < 0)
		return false;
	else
		return *(int32_t*)(g_MissionMgr.Data(sInst) + 0x28) == 5;*/

	XCALL(0x6AA890);
}

int32_t &CMissionMgr::State(int32_t id) {
	//return *(int32_t*)(*(int32_t*)(&g_MissionMgr + 0x688) + 0x6 * id);
	XCALL(0x6AA7C0);
}

int32_t &CMissionMgr::TopInst(void) { //mission's id
	XCALL(0x6AA790);
}

CMissionMgr *CMissionMgr::Data(int32_t id) {
	/*return (id >= 0 && id < *(int32_t*)(&g_MissionMgr + 0x684)) ?
		(CMissionMgr *)(*(int32_t*)(&g_MissionMgr + 0x4B8) + 0x4C * id) : (CMissionMgr *)(&g_MissionMgr + 0x4B8);*/

	XCALL(0x6AA660);
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