#include "CutsceneMgr.h"
#include "StreamManager.h"
#include "ActionTree.h"
#include "Screen.h"
#include "Game.h"
#include "Vector.h"
#include "Population.h"
#include "World.h"
#include "ColStore.h"
#include "WeaponInventory.h"
#include "Streaming.h"
#include "AudioManager.h"
#include "sndStream.h"
#include "Entity.h"
#include "MemoryHeap.h"
#include "Timer.h"
#include "TextManager.h"
#include "FileMgr.h"

bool &CCutsceneMgr::ms_loaded = *(bool*)0x20C5BE1;
bool &CCutsceneMgr::ms_loadStatus = *(bool*)0x20C5BE2;
bool &CCutsceneMgr::ms_animLoaded = *(bool*)0x20C5BE3;
bool &CCutsceneMgr::ms_running = *(bool*)0x20C5BE4;
bool &CCutsceneMgr::ms_MiniRunning = *(bool*)0x20C5BE5;
bool &CCutsceneMgr::ms_cutsceneProcessing = *(bool*)0x20C5BE6;
bool &CCutsceneMgr::ms_soundLoaded = *(bool*)0x20C5BE7;
bool &CCutsceneMgr::ms_useLodMultiplier = *(bool*)0x20C5BE8;
bool &CCutsceneMgr::m_MiniSoundReady = *(bool*)0x20C5BE9;
bool &CCutsceneMgr::ms_wasCutsceneSkipped = *(bool*)0x20C5BEA;

int32_t &CCutsceneMgr::ms_numObjectNames = *(int32_t*)0x20C5BF0;
int32_t &CCutsceneMgr::ms_numCutsceneObjs = *(int32_t*)0x20C5B18;

float &CCutsceneMgr::ms_cutsceneTimer = *(float*)0x20C5B1C;

char *CCutsceneMgr::ms_cutsceneName = (char*)0x20C5B20;
AM_Hierarchy **CCutsceneMgr::ms_pHierarchies = (AM_Hierarchy **)0x20C4B38;
CCutsceneObject **CCutsceneMgr::ms_pCutsceneObjects = (CCutsceneObject **)0x20C5B68;
ActionController *CCutsceneMgr::ms_CutSceneActionController = (ActionController*)0x20C5C0C;
char (*CCutsceneMgr::ms_CutsceneObjectNames)[64] = (char(*)[64])0x20C4C17;

CDirectory *CCutsceneMgr::ms_pCutsceneDir = (CDirectory *)0x20C4B34;

ActionNode *g_pCutSceneActionTree = *reinterpret_cast<ActionNode **>(0x20C4B30);

bool &bEverythingRemoved = *(bool*)0x20C5BE0;
bool &byte_20C5C08 = *(bool*)0x20C5C08;
int32_t &MI_FIRSTWEAPON = *(int32_t*)0xA136B0;
int32_t &MI_LASTWEAPON = *(int32_t*)0xA136B4;

char *g_string = (char *)0xC221A8;

void CCutsceneMgr::InjectHooks(void) {
	InjectHook(0x6C3BD0, &CCutsceneMgr::FinishMiniCutscene, PATCH_JUMP);
	InjectHook(0x6C38A0, &CCutsceneMgr::Reset, PATCH_JUMP);
	//InjectHook(0x6C3720, &CCutsceneMgr::Initialise, PATCH_JUMP);
	InjectHook(0x6C3DE0, &CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory, PATCH_JUMP);
	InjectHook(0x6C3AD0, &CCutsceneMgr::GetCutsceneTimeInMilleseconds, PATCH_JUMP);
	InjectHook(0x6C38B0, &CCutsceneMgr::LoadCutsceneSound, PATCH_JUMP);
	InjectHook(0x6C3B90, &CCutsceneMgr::StartMiniCutscene, PATCH_JUMP);
	InjectHook(0x6C3D50, &CCutsceneMgr::GetCutsceneJimmy, PATCH_JUMP);
	//InjectHook(0x6C45E0, &CCutsceneMgr::LoadCutsceneData, PATCH_JUMP);
}

void CCutsceneMgr::Reset(void) {
	g_pCutSceneActionTree = nullptr;
}

void CCutsceneMgr::Initialise(void) {
	ms_loaded = false;
	ms_running = false;
	ms_MiniRunning = false;
	ms_animLoaded = false;
	ms_cutsceneProcessing = false;
	ms_soundLoaded = false;
	ms_useLodMultiplier = false;
	ms_wasCutsceneSkipped = false;
	ms_loadStatus = false;
	ms_numObjectNames = 0;
	ms_numCutsceneObjs = 0;

	ms_pCutsceneDir = new CDirectory(NUM_DIRENTRIES);
	ms_pCutsceneDir->ReadDirFile("CUTS\\CUTS.DIR");

	for (int i = 0; i < NUM_HIERARCHIES; i++)
		ms_pHierarchies[i] = nullptr;

	for (int i = 0; i < NUM_CUTSCENEOBJS; i++)
		ms_pCutsceneObjects[i] = nullptr;

	ms_CutSceneActionController = new ActionController();

	printf("CCutsceneMgr was initialized!\n");
}

void CCutsceneMgr::CutSceneStartInitialization(void) {
	XCALL(0x6C3940);
}

void CCutsceneMgr::StartMiniCutscene(void) {
	if (ms_running)
		return;

	CutSceneStartInitialization();
	g_sndStream->SetPosition(nullptr, VOLUME1);
	Screamer->PlayCutSceneAudio();
	CCutsceneMgr::ms_running = true;
	CCutsceneMgr::ms_MiniRunning = true;
}

void CCutsceneMgr::FinishMiniCutscene(void) {
	g_StreamManager->StopStream(2);
	m_MiniSoundReady = false;
	ms_running = false;
	ms_cutsceneProcessing = false;
	ms_soundLoaded = false;
	ms_MiniRunning = false;
}

void CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory(void) {
	if (bEverythingRemoved) {
		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "bEverythingRemoved");
		CGame::DrasticTidyUpMemory(true);
	}
	else {
		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "Start");
		CVector coors = FindPlayerCoors();
		(*(CPopulation **)CPopulation::m_spInstance)->RemovePedsInSphere(coors, 120.0f);
		CWorld::ClearExcitingStuffFromArea(CVector::Zero, 4000.0f, true);
		CColStore::RemoveAllCollision();

		if (CGame::m_pRadar != nullptr)
			CGame::m_pRadar->RemoveRadarSections();

		bEverythingRemoved = true;

		if (&CWorld::Player != nullptr) { // CWorld::Player.pPed here, but currently this option
			for (int32_t idx = MI_FIRSTWEAPON; idx <= MI_LASTWEAPON; idx++) {
				if ( (*(CWeaponInventory**)(&CWorld::Player + 0x1C4))->Find(idx) != -1)
					CStreaming::SetModelIsDeletable(idx);
			}
		}

		CStreaming::DeleteAllRwObjects();
		CStreaming::RemoveUnusedModelsInLoadedList();

		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "CGame::DrasticTidyUpMemory()");
		CGame::DrasticTidyUpMemory(true);
		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "End");
	}
}

void CCutsceneMgr::LoadCutsceneData(char const *szCutsceneName, bool param) {
	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "Start");
	CMemoryHeap::PushMemId(CUTS_MEM_ID);
	
	ms_cutsceneProcessing = true;
	ms_wasCutsceneSkipped = false;
	ms_numObjectNames = 0;

	CTimer::Stop();

	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "Remove Zone Peds");
	if (!byte_20C5C08) //android doesn't have it
		CStreaming::RemoveCurrentZonesModels();

	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "Remove Vehicles");
	while (CStreaming::RemoveLoadedVehicle()) {}

	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "CStreaming::RemoveUnusedModelsInLoadedList()");
	CStreaming::RemoveUnusedModelsInLoadedList();

	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "RwFreeListPurgeAllFreeLists()");
	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "CGame::DrasticTidyUpMemory()");
	CGame::DrasticTidyUpMemory(true);

	char const *tmpNameCopy = szCutsceneName;
	strcpy_s(ms_cutsceneName, CUTSCNAMESIZE, szCutsceneName);

	char subtitleTextName[32];
	sprintf_s(subtitleTextName, 32, "%s_SUB", ms_cutsceneName);
	theTextManager->LoadConversationText(subtitleTextName);

	int32_t file = CFileMgr::OpenFile("CUTS\\CUTS.IMG", "r", true);

	LoadingScreen("CCutsceneMgr::LoadCutsceneData()", "FindMainPed()");
	CPlayerInfo Player = CWorld::Player;

	sprintf_s(g_string, 13, "%s.CUT", ms_cutsceneName);
}

void CCutsceneMgr::LoadCutsceneSound(char const *szCutsceneSoundName) {
	char fullName[260];
	char *tmpNameCopy = const_cast<char *>(szCutsceneSoundName);
	char *pLastBackSlash = strrchr(const_cast<char *>(szCutsceneSoundName), 92);
	char *pLastSlash = strrchr(const_cast<char *>(szCutsceneSoundName), 47);

	if (pLastSlash < pLastBackSlash)
		pLastSlash = pLastBackSlash;

	if (pLastSlash != nullptr)
		tmpNameCopy = pLastSlash++;

	strcpy_s(fullName, tmpNameCopy);
	strcat_s(fullName, ".rsm");
	Screamer->PrepareForCutScene(fullName, 1.0f);
	ms_soundLoaded = true;
}

CCutsceneObject *CCutsceneMgr::GetCutsceneJimmy(void) {
	if (!ms_cutsceneProcessing || ms_numObjectNames <= 0)
		return nullptr;

	int32_t nObjIndex = -1;
	for (int32_t i = 0; i < ms_numObjectNames; i++) {
		if (!_strnicmp(*ms_CutsceneObjectNames, "CS_PLAY", 7))
			nObjIndex = i;

		ms_CutsceneObjectNames++;
	}

	return (nObjIndex >= 0) ? ms_pCutsceneObjects[nObjIndex] : nullptr;
}

int16_t CCutsceneMgr::GetCutsceneTimeInMilleseconds(void) {
	return static_cast<int16_t>(ms_cutsceneTimer * 1000.0); 
}