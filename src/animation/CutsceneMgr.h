#pragma once
#include "patcher.h"

class CCutsceneMgr {
public:
	static bool &ms_running;
	static bool &m_MiniSoundReady;
	static bool &ms_cutsceneProcessing;
	static bool &ms_soundLoaded;
	static bool &ms_MiniRunning;

	static void FinishMiniCutscene(void);

	static void InjectHooks(void);
};