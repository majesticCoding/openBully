#include "Game.h"
#include "Screen.h"
#include "MissionMgr.h"
#include "MemoryHeap.h"
#include "DatManager.h"
#include "Area.h"
#include "Placeable.h"
#include "PathManager.h"
#include "SphereCollisionQuery.h"
#include "TxdStore.h"
#include "GameLogic.h"
#include "References.h"
#include "RwCamera.h"
#include "CameraManager.h"
#include "Occlusion.h"
#include "Debug.h"

HUDRadar *CGame::m_pRadar = *(HUDRadar **)0xC674CC;
char const *CGame::aDatFile = (char const *)0xBD0FA4;
int32_t CGame::currArea = *(int32_t*)0xBD1008;
int32_t CGame::currLevel = *(int32_t*)0xBD0FC4;

void CGame::InjectHooks(void) {
	//InjectHook(0x42EFE0, &CGame::Initialise, PATCH_JUMP);
}

void CGame::Initialise(char const *datFileName) {
	LoadingScreen("Loading the Game", "First loading screen");
	g_MissionMgr.Init("MissionBank", "Act/Missions.act");
	
	strcpy_s(const_cast<char *>(aDatFile), strlen(datFileName), datFileName); //TODO: check if it's ok
	CPlaceable::InitMatrixArray();

	CMemoryHeap::PushMemId(DATMANAGER_MEM_ID);
	//[!] breaks here!
	g_DATManager.Init();
	CAreaPopulationInfo::Init(); //With these CArea... may be some troubles cuz they have inheritance and vmts
	CAreaAmbientVehicleInfo::Init();
	CMemoryHeap::PopMemId();

	currLevel = 0;
	currArea = 0;

	LoadingScreen("CGame::Initialise", nullptr);
	
	if (g_PathManager == nullptr) 
		PathManager *g_PathManager = new PathManager();
	
	SphereCollisionQuery::Init();

	CMemoryHeap::PushMemId(TEXTURES_MEM_ID);
	LoadingScreen("Loading the Game", "Loading generic textures");
	
	int genericTXD = CTxdStore::AddTxdSlot("generic");
	CTxdStore::Create(genericTXD);
	CTxdStore::AddRef(genericTXD);
	
	LoadingScreen("Loading the Game", "Loading particles");
	int particleTXD = CTxdStore::AddTxdSlot("particle");
	CTxdStore::LoadTxd(particleTXD, "TXD/PARTICLE.NFT");
	CTxdStore::AddRef(particleTXD);

	CTxdStore::SetCurrentTxd(genericTXD);
	LoadingScreen("Loading the Game", "Setup game variables");
	CMemoryHeap::PopMemId();

	LoadingScreen(nullptr, "g_GameLogic.Init()");
	g_GameLogic.Init();

	CReferences::Init();
	LoadingScreen(nullptr, "theCameraManager()");

	g_CameraManager->SetRwCamera(g_RwCamera);
	g_CameraManager->Reset();

	/*DecalManager::StartUp(&g_DecalManager);
	ReflectionManager::Create(&g_ReflectionManager);
	AreaTransitionManager::StartUp(&AreaTransitionManager::ms_AreaTransitionManager);*/
	LoadingScreen(nullptr, "CDebug::DebugInitTextBuffer()");

	CDebug::ms_nCurrentTextLine = 0;

	/*ThePaths->CPathFind::Init();
	Weather::Init();
	CCullZones::Init();*/
	COcclusion::Init();
	//CCollision::Init();
	LoadingScreen(nullptr, "CWorld::Initialise()");

	//TODO: the rest
}

void CGame::DrasticTidyUpMemory(bool) {
	XCALL(0x4304E0);
}