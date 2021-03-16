#pragma once
#include "patcher.h"
#include "Directory.h"
#include "Hierarchy.h"
#include "CutsceneObject.h"
#include "ActionController.h"

#define CUTSCNAMESIZE 72
#define NUM_HIERARCHIES 10
#define NUM_CUTSCENEOBJS 30

class CCutsceneMgr {
public:
	static bool &ms_loaded;
	static bool &ms_running;
	static bool &m_MiniSoundReady;
	static bool &ms_animLoaded;
	static bool &ms_cutsceneProcessing;
	static bool &ms_soundLoaded;
	static bool &ms_MiniRunning;
	static bool &ms_useLodMultiplier;
	static bool &ms_wasCutsceneSkipped;
	static bool &ms_loadStatus;
	static int32_t &ms_numObjectNames;
	static int32_t &ms_numCutsceneObjs;

	static CDirectoryTemplate<CDirectoryInfo> *ms_pCutsceneDir;

	static char *ms_cutsceneName; //static char ms_cutsceneName[CUTSCNAMESIZE]
	static AM_Hierarchy **ms_pHierarchies; //not sure about type.. static AM_Hierarchy *ms_pHierarchies[10]
	static CCutsceneObject **ms_pCutsceneObjects; //static CCutsceneObject *ms_pCutsceneObjects[30]
	static ActionController *ms_CutSceneActionController;

	static void Initialise(void);
	static void FinishMiniCutscene(void);

	static void InjectHooks(void);
};