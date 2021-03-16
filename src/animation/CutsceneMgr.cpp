#include "CutsceneMgr.h"
#include "StreamManager.h"
#include "Directory.h"

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

char *CCutsceneMgr::ms_cutsceneName = (char*)0x20C5B20;
AM_Hierarchy **CCutsceneMgr::ms_pHierarchies = (AM_Hierarchy **)0x20C4B38;
CCutsceneObject **CCutsceneMgr::ms_pCutsceneObjects = (CCutsceneObject **)0x20C5B68;

CDirectoryTemplate<CDirectoryInfo> *CCutsceneMgr::ms_pCutsceneDir = (CDirectoryTemplate<CDirectoryInfo> *)0x20C4B34;

void CCutsceneMgr::InjectHooks(void) {
	InjectHook(0x6C3BD0, &CCutsceneMgr::FinishMiniCutscene, PATCH_JUMP);
	//InjectHook(0x6C3720, &CCutsceneMgr::Initialise, PATCH_JUMP);
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

	ms_pCutsceneDir = new CDirectoryTemplate<CDirectoryInfo>(NUM_DIRENTRIES);
	ms_pCutsceneDir->ReadDirFile("CUTS\\CUTS.DIR");

	for (int32_t i = 0; i < NUM_HIERARCHIES; i++) {
		ms_pHierarchies[i] = nullptr;
	}

	for (int32_t i = 0; i < NUM_CUTSCENEOBJS; i++) {
		ms_pCutsceneObjects[i] = nullptr;
	}

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