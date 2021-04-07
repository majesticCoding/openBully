#pragma once
#include "patcher.h"
#include "Directory.h"
#include "Hierarchy.h"
#include "Model.h"
#include "AnimationManager.h"
#include "CutsceneObject.h"
#include "ActionController.h"
#include "CameraManager.h"

#define CUTSCNAMESIZE 72
#define NUM_HIERARCHIES 10
#define NUM_CUTSCENEOBJS 30
#define NUM_CUTSSPECIALS 30

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
	static int32_t &ms_iCurrentSubtitle;
	static int32_t &ms_iNumSubtitles;
	static uint32_t &ms_uNumModels;
	static float &ms_cutsceneTimer;

	static CDirectory **ms_pCutsceneDir;

	static char *ms_cutsceneName; //static char ms_cutsceneName[CUTSCNAMESIZE]
	static AM_Hierarchy **ms_pHierarchies; //static AM_Hierarchy *ms_pHierarchies[10]
	static AM_Model **ms_pModels;
	static CCutsceneObject **ms_pCutsceneObjects; //static CCutsceneObject *ms_pCutsceneObjects[30]
	static ActionController **ms_CutSceneActionController;
	static int32_t **ms_SubtitleInfoArray; //find out the real type
	static char (*ms_CutsceneObjectNames)[64]; //static char *ms_CutsceneObjectNames[60][64]

	static void Initialise(void);
	static void CutSceneStartInitialization(void);
	static void Reset(void);
	static void StartMiniCutscene(void);
	static void FinishMiniCutscene(void);
	static void RemoveEverythingBecauseCutsceneDoesntFitInMemory(void);
	static void LoadCutsceneData(char const *szCutsceneName, bool param);
	static void LoadCutsceneSound(char const *szCutsceneSoundName);
	static void DeleteCutsceneData(void);
	static int16_t GetCutsceneTimeInMilleseconds(void);
	static int32_t GetNumberOfPropAnimsToUpdate(void);
	static CCutsceneObject *GetCutsceneJimmy(void);

	static void InjectHooks(void);
};