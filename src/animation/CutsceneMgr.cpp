#include "CutsceneMgr.h"
#include "StreamManager.h"

bool &CCutsceneMgr::ms_running = *(bool*)0x20C5BE4;
bool &CCutsceneMgr::m_MiniSoundReady = *(bool*)0x20C5BE9;
bool &CCutsceneMgr::ms_cutsceneProcessing = *(bool*)0x20C5BE6;
bool &CCutsceneMgr::ms_soundLoaded = *(bool*)0x20C5BE7;
bool &CCutsceneMgr::ms_MiniRunning = *(bool*)0x20C5BE9;


void CCutsceneMgr::InjectHooks(void) {
	InjectHook(0x6C3BD0, &CCutsceneMgr::FinishMiniCutscene, PATCH_JUMP);
}

void CCutsceneMgr::FinishMiniCutscene(void) {
	g_StreamManager->StopStream(2);
	m_MiniSoundReady = false;
	ms_running = false;
	ms_cutsceneProcessing = false;
	ms_soundLoaded = false;
	ms_MiniRunning = false;
}