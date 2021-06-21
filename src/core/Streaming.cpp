#include "hook.h"
#include "Streaming.h"

bool &CStreaming::ms_disableStreaming = *(bool*)0xCA3984;

void CStreaming::SetModelIsDeletable(int32_t modelId) {
	XCALL(0x52FE40);
}

void CStreaming::DeleteAllRwObjects(void) {
	XCALL(0x52F0E0);
}

void CStreaming::RemoveUnusedModelsInLoadedList(void) {
	XCALL(0x530B50);
}

void CStreaming::RemoveCurrentZonesModels(void) {
	XCALL(0x52D9A0);
}

void CStreaming::SetMissionDoesntRequireSpecialChar(int32_t modelId) {
	XCALL(0x530040);
}

bool CStreaming::RemoveLoadedVehicle(void) {
	XCALL(0x530060);
}

void CStreaming::RemoveModel(int32_t modelId) {
	XCALL(0x52F640);
}

void CStreaming::RequestModel(int32_t modelId, int32_t flag) {
	XCALL(0x532020);
}