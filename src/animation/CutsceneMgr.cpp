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

CDirectory *CCutsceneMgr::ms_pCutsceneDir = (CDirectory *)0x20C4B34;

ActionNode *g_pCutSceneActionTree = *(ActionNode **)0x20C4B30;

bool &g_bIsEverythingRemovedForCutscene = *(bool*)0x20C5BE0; //custom name
int32_t &MI_FIRSTWEAPON = *(int32_t*)0xA136B0;
int32_t &MI_LASTWEAPON = *(int32_t*)0xA136B4;


void CCutsceneMgr::InjectHooks(void) {
	InjectHook(0x6C3BD0, &CCutsceneMgr::FinishMiniCutscene, PATCH_JUMP);
	InjectHook(0x6C38A0, &CCutsceneMgr::Reset, PATCH_JUMP);
	//InjectHook(0x6C3720, &CCutsceneMgr::Initialise, PATCH_JUMP);
	InjectHook(0x6C3DE0, &CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory, PATCH_JUMP);
	InjectHook(0x6C3AD0, &CCutsceneMgr::GetCutsceneTimeInMilleseconds, PATCH_JUMP);
	InjectHook(0x6C38B0, &CCutsceneMgr::LoadCutsceneSound, PATCH_JUMP);
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

	//ms_pCutsceneDir = (CDirectory*)CDirectoryTemplate<CDirectoryInfo>(NUM_DIRENTRIES);
	//ms_pCutsceneDir->ReadDirFile("CUTS\\CUTS.DIR");

	memset(ms_pHierarchies, NULL, NUM_HIERARCHIES * sizeof(ms_pHierarchies));
	memset(ms_pCutsceneObjects, NULL, NUM_CUTSCENEOBJS * sizeof(ms_pCutsceneObjects));

	ms_CutSceneActionController = new ActionController();

	printf("CCutsceneMgr was initialized!\n");
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
	if (g_bIsEverythingRemovedForCutscene) {
		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "bEverythingRemoved");
		CGame::DrasticTidyUpMemory(true);
	}
	else {
		LoadingScreen("CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()", "Start");
		CVector coors = FindPlayerCoors();
		(*(CPopulation **)CPopulation::m_spInstance)->RemovePedsInSphere(coors, 120.0f);
		CWorld::ClearExcitingStuffFromArea(CVector::Zero, 4000.0f, 1);
		CColStore::RemoveAllCollision();

		if (CGame::m_pRadar != nullptr)
			CGame::m_pRadar->RemoveRadarSections();

		g_bIsEverythingRemovedForCutscene = true;

		if ((int32_t*)CWorld::Player != nullptr) { // CWorld::Player.pPed here, but currently this option
			for (int32_t idx = MI_FIRSTWEAPON; idx <= MI_LASTWEAPON; idx++) {
				if ( (*(CWeaponInventory**)(CWorld::Player + 0x1C4))->Find(idx) != -1)
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

void CCutsceneMgr::LoadCutsceneSound(char const *name) {
	char fullName[260];
	char *tmpNameCopy = const_cast<char *>(name);
	char *pLastBackSlash = strrchr(const_cast<char *>(name), 92);
	char *pLastSlash = strrchr(const_cast<char *>(name), 47);

	if (pLastSlash < pLastBackSlash)
		pLastSlash = pLastBackSlash;

	if (pLastSlash != nullptr)
		tmpNameCopy = pLastSlash++;

	strcpy_s(fullName, tmpNameCopy);
	strcat_s(fullName, ".rsm");
	Screamer->PrepareForCutScene(fullName, 1.0f);
	ms_soundLoaded = 1;
}

int16_t CCutsceneMgr::GetCutsceneTimeInMilleseconds(void) {
	return static_cast<int16_t>(ms_cutsceneTimer * 1000.0); 
}